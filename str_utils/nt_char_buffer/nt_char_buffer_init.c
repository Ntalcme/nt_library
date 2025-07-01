#include "nt_char_buffer.h"

int nt_char_buffer_init(nt_char_buffer *buf, int has_arg, ...)
{
    va_list args;
    size_t capacity;

    capacity = NT_CHAR_BUFFER_INIT_CAPACITY;
    if(has_arg)
    {
        va_start(args, has_arg);
        capacity = va_arg(args, int);
        va_end(args);
    }

    buf->data = malloc(sizeof(char) * capacity);
    
    if (!buf->data) return (0);

    buf->len = 0;
    buf->capacity = NT_CHAR_BUFFER_INIT_CAPACITY;
    buf->data[0] = '\0';

    return (1);
}
