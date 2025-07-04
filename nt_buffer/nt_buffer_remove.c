# include "nt_buffer.h"

/**
 * Remove an element of the nt_buffer at an index
 * Elements after the removed one are shifted to fill the gap
 * @param buf The buffer's pointer
 * @param i The index
 */
void nt_buffer_remove(nt_buffer *buf, size_t i)
{
    size_t bytes_to_move;

    if (!buf || !buf->data || i >= buf->element_count) return;

    if (buf->destructor) {
        buf->destructor((char *)buf->data + (i * buf->element_size));
    }

    bytes_to_move = (buf->element_count - 1 - i) * buf->element_size;
    nt_memmove
    (
        (char *)buf->data + (i * buf->element_size),       
        (char *)buf->data + ((i + 1) * buf->element_size), 
        bytes_to_move                                       
    );

    buf->element_count--;
}
