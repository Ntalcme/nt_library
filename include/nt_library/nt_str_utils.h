#ifndef NT_STR_UTILS_H
#define NT_STR_UTILS_H

#include "nt_buffer.h"
#include <stdlib.h>

size_t     nt_strlen(const char *str);
char      *nt_strdup(const char *str);
nt_buffer *nt_parse(const char *str, const char sep);
char      *nt_join(nt_buffer *buf, const char sep);

extern const char  GLOBAL_NULL_CHAR;
extern char *const GLOBAL_NULL_PTR;
extern char *const GLOBAL_EMPTY_STRING;

#endif
