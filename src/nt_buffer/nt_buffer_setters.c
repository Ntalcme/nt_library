#include "libnt/nt_buffer.h"
#include "nt_buffer_internal.h"

int nt_buffer_set_data(nt_buffer *buf, void *new_value)
{
    if (!buf)
        return (1);
    buf->data = new_value;
    return (0);
}

int nt_buffer_set_count(nt_buffer *buf, size_t new_value)
{
    if (!buf)
        return (1);
    buf->element_count = new_value;
    return (0);
}

int nt_buffer_set_capacity(nt_buffer *buf, size_t new_value)
{
    if (!buf)
        return (1);
    buf->capacity = new_value;
    return (0);
}
