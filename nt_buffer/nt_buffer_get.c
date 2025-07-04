# include "nt_buffer.h"

/**
 * Get a pointer of nt_buffer's element at an index
 * @param buf The buffer's pointer
 * @param i The index
 * @return A generic pointer (void*) to the element at the specified index
 * Returns NULL if the buffer is invalid, empty or the index is out of bounds
 * The returned pointed needs to be cast to the appropriate element type
 */
void *nt_buffer_get(nt_buffer *buf, size_t i)
{
    if (!buf || !buf->data || i >= buf->element_count) return (NULL);

    return (void *)((unsigned char *)buf->data + (i * buf->element_size));
}
