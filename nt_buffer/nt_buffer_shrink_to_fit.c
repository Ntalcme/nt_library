#include "nt_buffer.h"

/**
 * Reallocs only the necessary memory for the buffer's data
 * @param buf The buffer's pointer
 * @return 1 if failed, 0 if success
 */
nt_status nt_buffer_shrink_to_fit(nt_buffer *buf)
{
    void *new_data;

    if (!buf || !buf->data || buf->element_count == buf->capacity)
        return (NT_SUCCESS);

    if (buf->element_count == 0)
    {
        free(buf->data);
        buf->data = NULL;
        buf->capacity = 0;
        return (NT_SUCCESS);
    }

    new_data = realloc(buf->data, buf->element_count * buf->element_size);

    if (!new_data)
        return (NT_ERR_ALLOC);
    buf->data = new_data;
    buf->capacity = buf->element_count;

    return (NT_SUCCESS);
}
