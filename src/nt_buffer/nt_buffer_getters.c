#include "libnt/nt_buffer.h"
#include "nt_buffer_internal.h"

/**
 * Get a pointer of nt_buffer's element at an index
 * @param buf The buffer's pointer
 * @param i The index
 * @return A generic pointer (void*) to the element at the specified index
 * Returns NULL if the buffer is invalid, empty or the index is out of bounds
 * The returned pointed needs to be cast to the appropriate element type
 */
static const void *nt_buffer_get_element(const nt_buffer *buf, size_t i)
{
    if (!buf || !buf->data || i >= buf->element_count)
        return (NULL);

    return (void *)((unsigned char *)buf->data + (i * buf->element_size));
}

const void *nt_buffer_get_data(const nt_buffer *buf)
{
    if (!buf)
        return (NULL);
    return (buf->data);
}

size_t nt_buffer_get_count(const nt_buffer *buf)
{
    if (!buf)
        return (0);
    return (buf->element_count);
}

size_t nt_buffer_get_element_size(const nt_buffer *buf)
{
    if (!buf)
        return (0);
    return (buf->element_size);
}

size_t nt_buffer_get_capacity(const nt_buffer *buf)
{
    if (!buf)
        return (0);
    return (buf->capacity);
}
