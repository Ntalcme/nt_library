#include "nt_buffer.h"

/**
 * Frees all dynamically allocated memory within the buffer and resets its state
 * to empty The buffer itself is not freed by this function
 * @param buf The buffer's pointer
 */
void nt_buffer_free(nt_buffer *buf)
{
    size_t i;

    if (!buf)
        return;

    if (buf->data)
    {
        if (buf->destructor)
        {
            for (i = 0; i < buf->element_count; i++)
            {
                buf->destructor((char *)buf->data + (i * buf->element_size));
            }
        }
        free(buf->data);
        buf->data = NULL;
    }
    buf->element_count = 0;
    buf->capacity = 0;
    buf->destructor = NULL;
}
