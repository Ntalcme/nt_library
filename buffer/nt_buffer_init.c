# include "nt_buffer.h"

int nt_buffer_init(nt_buffer *buf, size_t capacity, size_t element_size, void (*destructor)(void*))
{
    if (!buf || element_size == 0) return (1);

    buf->data = NULL;
    if (capacity > 0)
    {
        buf->data = malloc(element_size * capacity);
        if (!buf) return (1);
    }
    buf->capacity = capacity;
    buf->len = 0;
    buf->element_size = element_size;
    buf->destructor = destructor;
    return (0);
}
