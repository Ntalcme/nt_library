# include "nt_buffer.h"

void *nt_buffer_get(nt_buffer *buf, size_t i)
{
    if (!buf || !buf->data || i >= buf->len) return (NULL);

    return (void *)((unsigned char *)buf->data + (i * buf->element_size));
}
