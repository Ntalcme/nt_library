#include "nt_char_buffer.h"

int nt_char_buffer_add_char(nt_char_buffer *buf, const char c)
{
    size_t new_capacity;
    char *tmp;

    if(buf->capacity <= 0)
    {
        buf->capacity = NT_CHAR_BUFFER_INIT_CAPACITY;
    }

    if (buf->len + 1 >= buf->capacity)
    {
        new_capacity = buf->capacity * 2;
        tmp = realloc(buf->data, sizeof(char) * new_capacity);
        if (!tmp)
        {
            return (0);
        }
        buf->data = tmp;
        buf->capacity = new_capacity;
    }

    buf->data[buf->len] = c;
    buf->len++;
    buf->data[buf->len] = '\0';
    
    return (1);
}