#ifndef NT_CHAR_BUFFER
#define NT_CHAR_BUFFER

# include <stdlib.h>
# include <stdarg.h>

typedef struct nt_char_buffer
{
    char *data;
    size_t len;
    size_t capacity;
} nt_char_buffer;

int nt_char_buffer_add_char(nt_char_buffer *buf, const char c);
int nt_char_buffer_init(nt_char_buffer *buf, int has_arg, ...);

#define NT_CHAR_BUFFER_INIT_LEN 0
#define NT_CHAR_BUFFER_INIT_CAPACITY 16

#endif