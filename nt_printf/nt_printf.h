#ifndef NT_PRINTF_H
#define NT_PRINTF_H

# include <stdarg.h>
# include "../conversion/nt_conversion.h"
# include "../str_utils/nt_str_utils.h"
# include "../fd/nt_fd.h"

ssize_t nt_printf(const char *str, ...);

#endif
