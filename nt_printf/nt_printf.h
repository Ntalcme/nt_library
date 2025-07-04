#ifndef NT_PRINTF_H
#define NT_PRINTF_H

#include "../conversion/nt_conversion.h"
#include "../fd/nt_fd.h"
#include "../str_utils/nt_str_utils.h"
#include <stdarg.h>

ssize_t nt_printf(const char *str, ...);

#endif
