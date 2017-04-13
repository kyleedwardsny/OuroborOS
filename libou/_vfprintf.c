#include <ouroboros/stdio.h>
#include <ouroboros/string.h>

#include <stdint.h>

#define FLAGS_LEFT_JUSTIFY	(0x01)
#define FLAGS_FORCE_SIGN	(0x02)
#define FLAGS_SPACE_IF_NO_SIGN	(0x04)
#define FLAGS_HEX_OCTAL_PREFIX	(0x08)
#define FLAGS_LEFT_PAD_ZEROES	(0x10)

#define LENGTH_NONE		(0)
#define LENGTH_HH		(1)
#define LENGTH_H		(2)
#define LENGTH_L		(3)
#define LENGTH_LL		(4)
#define LENGTH_J		(5)
#define LENGTH_Z		(6)
#define LENGTH_T		(7)
#define LENGTH_LONG_DOUBLE	(8)

struct specifier {
	unsigned int flags;
	int min_characters;
	int precision;
	unsigned int length;
};

typedef ou_ssize_t (*write_cb)(void *cb_data, const void *data, size_t len);

static const char HEX_LOWER[] = "0123456789abcdef";
static const char HEX_UPPER[] = "0123456789ABCDEF";

static void byte_to_hex(char *hex, uint8_t byte, int lower)
{
	const char *hex_table;

	if (lower) {
		hex_table = HEX_LOWER;
	} else {
		hex_table = HEX_UPPER;
	}

	hex[0] = hex_table[(byte >> 4) & 0xF];
	hex[1] = hex_table[(byte >> 0) & 0xF];
}

static int print_hex(write_cb write_cb, void *cb_data, unsigned long long num, unsigned int flags, int min_characters, int precision, int lower)
{
	int retval = -1;
	/* 1 for + sign, 2 for 0x prefix, and room for 2 copies of num to account for justification */
	char buf[1 + 2 + sizeof(num) * 2 + sizeof(num) * 2];
	size_t num_digits = sizeof(num) * 2;
	size_t num_zeroes = 0;
	size_t num_spaces = 0;
	size_t total_length;
	unsigned long long mask = 0xF000000000000000;
	size_t index = 1 + 2;
	const char *prefix = NULL;
	char chr;
	size_t i;
	uint8_t digit;

	while (!(num & mask) && mask) {
		mask >>= 4;
		num_digits--;
		index++;
	}

	if (num_digits <= 0) {
		num_digits = 0;
	}

	if (precision > (int) num_digits) { /* Don't need to check if precision > 0, because it will be if this evaluates to true */
		num_zeroes = precision - num_digits;
	}

	total_length = num_zeroes + num_digits;
	if (flags & FLAGS_HEX_OCTAL_PREFIX) {
		prefix = lower ? "0x" : "0X";
		total_length += 2;
	}

	if (min_characters > (int) total_length) {
		if (flags & FLAGS_LEFT_PAD_ZEROES) {
			num_zeroes = min_characters - (total_length - num_digits - num_zeroes);
		} else {
			num_spaces = min_characters - total_length;
		}
		total_length = min_characters;
	}

	if (!(flags & FLAGS_LEFT_JUSTIFY)) {
		for (i = 0; i < num_spaces; i++) {
			if (write_cb(cb_data, " ", 1) < 0) {
				goto ret;
			}
		}
	}

	if (prefix) {
		if (write_cb(cb_data, prefix, ou_strlen(prefix)) < 0) {
			goto ret;
		}
	}

	for (i = 0; i < num_zeroes; i++) {
		if (write_cb(cb_data, "0", 1) < 0) {
			goto ret;
		}
	}

	for (i = 0; i < num_digits; i++) {
		digit = (num >> ((num_digits - i - 1) * 4)) & 0xF;
		chr = lower ? HEX_LOWER[digit] : HEX_UPPER[digit];
		if (write_cb(cb_data, &chr, 1) < 0) {
			goto ret;
		}
	}

	if (flags & FLAGS_LEFT_JUSTIFY) {
		for (i = 0; i < num_spaces; i++) {
			if (write_cb(cb_data, " ", 1) < 0) {
				goto ret;
			}
		}
	}

	/* Success */
	retval = total_length;
ret:
	return retval;
}

static long long get_int_argument_signed(va_list *args, unsigned int length)
{
	switch (length) {
	case LENGTH_HH:
		return (char) va_arg(*args, int);

	case LENGTH_H:
		return (short) va_arg(*args, int);

	case LENGTH_L:
		return va_arg(*args, long);

	case LENGTH_LL:
		return va_arg(*args, long long);

	case LENGTH_J:
		return va_arg(*args, intmax_t);

	case LENGTH_Z:
		return va_arg(*args, size_t);

	case LENGTH_T:
		return va_arg(*args, ptrdiff_t);

	default:
		return va_arg(*args, int);
	}
}

static unsigned long long get_int_argument_unsigned(va_list *args, unsigned int length)
{
	switch (length) {
	case LENGTH_HH:
		return (unsigned char) va_arg(*args, unsigned int);

	case LENGTH_H:
		return (unsigned short) va_arg(*args, unsigned int);

	case LENGTH_L:
		return va_arg(*args, unsigned long);

	case LENGTH_LL:
		return va_arg(*args, unsigned long long);

	case LENGTH_J:
		return va_arg(*args, intmax_t);

	case LENGTH_Z:
		return va_arg(*args, size_t);

	case LENGTH_T:
		return va_arg(*args, ptrdiff_t);

	default:
		return va_arg(*args, unsigned int);
	}
}

static int print_pointer(write_cb write_cb, void *cb_data, const void *ptr)
{
	int retval = -1;
	size_t i;
	char buf[sizeof(ptr) * 2];

	for (i = 0; i < sizeof(ptr); i++) {
		byte_to_hex(buf + (i * 2), (((size_t) ptr) >> ((sizeof(ptr) - i - 1) * 8)) & 0xFF, 0);
	}

	if (write_cb(cb_data, buf, sizeof(buf)) < 0) {
		goto ret;
	}

	/* Success */
	retval = sizeof(buf);
ret:
	return retval;
}

static int parse_digit(int original, char digit)
{
	if (original < 0) {
		original = 0;
	}

	return original * 10 + digit - '0';
}

static int is_digit(char digit)
{
	return '0' <= digit && digit <= '9';
}

static int parse_specifier(write_cb write_cb, void *cb_data, int written, const char **format, va_list *args)
{
	int retval = -1;
	size_t total_len = 0;
	int stop;

	unsigned int flags = 0;
	int min_characters = -1;
	int precision = -1;
	unsigned int length = LENGTH_NONE;

	char chr;
	const char *str;
	size_t str_len;
	int *written_arg;
	const void *ptr;
	int result;

	unsigned long long unum;
	long long num;

	stop = 0;
	while (!stop) {
		switch (**format) {
		case '-':
			flags |= FLAGS_LEFT_JUSTIFY;
			(*format)++;
			break;

		case '+':
			flags |= FLAGS_FORCE_SIGN;
			(*format)++;
			break;

		case ' ':
			flags |= FLAGS_SPACE_IF_NO_SIGN;
			(*format)++;
			break;

		case '#':
			flags |= FLAGS_HEX_OCTAL_PREFIX;
			(*format)++;
			break;

		case '0':
			flags |= FLAGS_LEFT_PAD_ZEROES;
			(*format)++;
			break;

		default:
			stop = 1;
			break;
		}
	}

	stop = 0;
	while (!stop) {
		if (**format == '*') {
			min_characters = va_arg(*args, int);
			(*format)++;
			stop = 1;
		} else if (is_digit(**format)) {
			min_characters = parse_digit(min_characters, **format);
			(*format)++;
		} else {
			stop = 1;
		}
	}

	if (**format == '.') {
		(*format)++;

		stop = 0;
		while (!stop) {
			if (**format == '*') {
				precision = va_arg(*args, int);
				stop = 1;
				(*format)++;
			} else if (is_digit(**format)) {
				precision = parse_digit(precision, **format);
				(*format)++;
			} else {
				stop = 1;
			}
		}
	}

	switch (**format) {
	case 'h':
		(*format)++;
		if (**format == 'h') {
			length = LENGTH_HH;
			(*format)++;
		} else {
			length = LENGTH_H;
		}
		break;

	case 'l':
		(*format)++;
		if (**format == 'l') {
			length = LENGTH_LL;
			(*format)++;
		} else {
			length = LENGTH_L;
		}
		break;

	case 'j':
		length = LENGTH_J;
		(*format)++;
		break;

	case 'z':
		length = LENGTH_Z;
		(*format)++;
		break;

	case 't':
		length = LENGTH_T;
		(*format)++;
		break;

	case 'L':
		length = LENGTH_LONG_DOUBLE;
		(*format)++;
		break;
	}

	switch (**format) {
	case '%':
		write_cb(cb_data, "%", 1);
		total_len++;
		(*format)++;
		break;

	case 'd':
	case 'i':
		/* TODO */
		(*format)++;
		break;

	case 'u':
		/* TODO */
		(*format)++;
		break;

	case 'o':
		/* TODO */
		(*format)++;
		break;

	case 'x':
		unum = get_int_argument_unsigned(args, length);
		result = print_hex(write_cb, cb_data, unum, flags, min_characters, precision, 1);
		if (result < 0) {
			goto ret;
		}
		total_len += result;
		(*format)++;
		break;

	case 'X':
		unum = get_int_argument_unsigned(args, length);
		result = print_hex(write_cb, cb_data, unum, flags, min_characters, precision, 0);
		if (result < 0) {
			goto ret;
		}
		total_len += result;
		(*format)++;
		break;

	case 'f':
		/* TODO */
		(*format)++;
		break;

	case 'F':
		/* TODO */
		(*format)++;
		break;

	case 'e':
		/* TODO */
		(*format)++;
		break;

	case 'E':
		/* TODO */
		(*format)++;
		break;

	case 'g':
		/* TODO */
		(*format)++;
		break;

	case 'G':
		/* TODO */
		(*format)++;
		break;

	case 'a':
		/* TODO */
		(*format)++;
		break;

	case 'A':
		/* TODO */
		(*format)++;
		break;

	case 'c':
		chr = va_arg(*args, int);
		if (write_cb(cb_data, &chr, 1) < 0) {
			goto ret;
		}
		total_len++;
		(*format)++;
		break;

	case 's':
		str = va_arg(*args, const char *);
		str_len = ou_strlen(str);
		if (write_cb(cb_data, str, str_len) < 0) {
			goto ret;
		}
		total_len += str_len;
		(*format)++;
		break;

	case 'p':
		ptr = va_arg(*args, const void *);
		result = print_pointer(write_cb, cb_data, ptr);
		if (result < 0) {
			goto ret;
		}
		total_len += result;
		(*format)++;
		break;

	case 'n':
		written_arg = va_arg(*args, int *);
		*written_arg = written;
		(*format)++;
		break;

	default: /* ??? */
		goto ret;
	}

	/* Success */
	retval = total_len;
ret:
	return retval;
}

int _ou_vfprintf(write_cb write_cb, void *cb_data, const char *format, va_list args)
{
	const char *found_specifier;
	int retval = -1;
	int total_len = 0;
	int result;

	while (*format) {
		found_specifier = format;
		do { /* We already know *found_specifier is not null */
			if (*found_specifier == '%') {
				break;
			}
			found_specifier++;
		} while (*found_specifier);

		if (write_cb(cb_data, format, found_specifier - format) < 0) {
			goto ret;
		}
		total_len += found_specifier - format;

		if (*found_specifier) {
			found_specifier++;

			result = parse_specifier(write_cb, cb_data, total_len, &found_specifier, &args);
			if (result >= 0) {
				total_len += result;
			} else {
				goto ret;
			}
		}

		format = found_specifier;
	}

	/* Success */
	retval = total_len;
ret:
	return retval;
}
