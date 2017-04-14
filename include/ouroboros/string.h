#ifndef OUROBOROS_STRING_H
#define OUROBOROS_STRING_H

#include <ouroboros/stddef.h>

char *ou_strcpy(char *dst, const char *src);

size_t ou_strlen(const char *str);

const char *ou_strchr(const char *str, int character);

void *ou_memcpy(void *destination, const void *source, ou_size_t len);

#endif /* OUROBOROS_STRING_H */
