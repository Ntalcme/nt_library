# include "nt_buffer.h"

/**
 * Reallocs only the necessary memory for the buffer's data
 * @param buf The buffer's pointer
 * @return 1 if failed, 0 if success
 */
int nt_buffer_shrink_to_fit(nt_buffer *buf)
{
    void *new_data;

    if (!buf || !buf->data || buf->element_count == buf->capacity) return (0);

    if (buf->element_count == 0)
    {
        free(buf->data);
        buf->data = NULL;
        buf->capacity = 0;
    }

    new_data = realloc(buf->data, buf->element_count * buf->element_size);

    if (!new_data) return (1);
    buf->data = new_data;
    buf->capacity = buf->element_count;

    return (0);
}