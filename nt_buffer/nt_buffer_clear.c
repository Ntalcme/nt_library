#include "nt_buffer.h"

/**
 * Clear all elements of the buffer but keeps the allocated memory
 * @param buf The buffer's pointer
 */
void nt_buffer_clear(nt_buffer *buf)
{
    if (!buf)
        return;

    if (buf->destructor && buf->data)
    {
        for (size_t i = 0; i < buf->element_count; i++)
        {
            buf->destructor((char *)buf->data + (i * buf->element_size));
        }
    }
    buf->element_count = 0;
}
