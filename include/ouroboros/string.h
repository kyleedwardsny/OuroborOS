#ifndef OUROBOROS_STRING_H
#define OUROBOROS_STRING_H

#include <ouroboros/stddef.h>

char *ou_strcpy(char *dst, const char *src);

ou_size_t ou_strlen(const char *str);

ou_size_t ou_strnlen(const char *str, ou_size_t len);

const char *ou_strchr(const char *str, int character);

void *ou_memcpy(void *destination, const void *source, ou_size_t len);

void *ou_memrcpy(void *destination, const void *source, ou_size_t len);

int ou_memcmp(const void *ptr1, const void *ptr2, ou_size_t len);

void *ou_memmove(void *destination, const void *source, ou_size_t len);

void *ou_memchr(const void *ptr, int value, ou_size_t len);

void *ou_memset(void *ptr, int value, ou_size_t len);

#endif /* OUROBOROS_STRING_H */
