# include "nt_buffer.h"

void nt_buffer_remove(nt_buffer *buf, size_t i)
{
    size_t bytes_to_move;

    if (!buf || !buf->data || i >= buf->len) return;

    bytes_to_move = (buf->len - 1 - i) * buf->element_size;
    nt_memmove
    (
        (char *)buf->data + (i * buf->element_size),       
        (char *)buf->data + ((i + 1) * buf->element_size), 
        bytes_to_move                                       
    );

    buf->len--;
}