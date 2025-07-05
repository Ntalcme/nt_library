#ifndef NT_PRINTF_H
#define NT_PRINTF_H

#include "nt_conversion.h"
#include "nt_fd.h"
#include "nt_str_utils.h"
#include <stdarg.h>

ssize_t nt_printf(const char *str, ...);

#endif
