// ------------------------------------------------------------------------------------------------
// printf.h
// ------------------------------------------------------------------------------------------------

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

int vsscanf(const char *str, const char *fmt, va_list args);
int sscanf(const char *str, const char *fmt, ...);

int vsnprintf(char *str, uint32_t size, const char *fmt, va_list args);
int snprintf(char *str, uint32_t size, const char *fmt, ...);

unsigned long int strtoul(const char *nptr, char **endptr, int base);
