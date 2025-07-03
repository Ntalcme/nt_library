#ifndef NT_STR_UTILS_H
#define NT_STR_UTILS_H

# include <stdlib.h>
# include "../nt_buffer/nt_buffer.h"

size_t nt_strlen(const char *str);
char *nt_strdup(const char *str);

extern const char GLOBAL_NULL_CHAR;
extern char *const GLOBAL_NULL_PTR;

#endif
