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
		if (**format == 'h') {
			length = LENGTH_HH;
			(*format)++;
		} else {
			length = LENGTH_H;
		}
		(*format)++;
		break;

	case 'l':
		if (**format == 'l') {
			length = LENGTH_LL;
			(*format)++;
		} else {
			length = LENGTH_L;
		}
		(*format)++;
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
		break;

	case 'u':
		/* TODO */
		break;

	case 'o':
		/* TODO */
		break;

	case 'x':
		/* TODO */
		break;

	case 'X':
		/* TODO */
		break;

	case 'f':
		/* TODO */
		break;

	case 'F':
		/* TODO */
		break;

	case 'e':
		/* TODO */
		break;

	case 'E':
		/* TODO */
		break;

	case 'g':
		/* TODO */
		break;

	case 'G':
		/* TODO */
		break;

	case 'a':
		/* TODO */
		break;

	case 'A':
		/* TODO */
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
