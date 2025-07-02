#include "nt_str_utils.h"

DEFINE_BUFFER_TYPE(char, char)
DEFINE_BUFFER_TYPE(char *, ptr_char)

char **nt_parse(const char *str)
{
    nt_char_buffer tmp;
    nt_ptr_char_buffer res;
    size_t i;
}