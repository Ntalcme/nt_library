#ifndef NT_CHAR_BUFFER
#define NT_CHAR_BUFFER

# include <stdlib.h>

int nt_char_buffer_add_char(nt_char_buffer *buf, const char c);

typedef struct nt_char_buffer
{
    char *data;
    size_t len;
    size_t capacity;
} nt_char_buffer;

#endif