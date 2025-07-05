#include <libnt/nt_buffer.h>

/**
 * Add an element to a nt_buffer struct
 * @param buf The buffer's pointer
 * @param elt The element to add
 * @return 1 if failed, 0 if success
 */
int nt_buffer_add(nt_buffer *buf, const void *elt)
{
    size_t new_cap;
    void  *new_data;

    if (!buf || !elt)
        return (1);

    if (buf->element_count == buf->capacity)
    {
        new_cap = buf->capacity ? buf->capacity * 2 : 4;
        new_data = realloc(buf->data, new_cap * buf->element_size);
        if (!new_data)
            return (1);
        buf->data = new_data;
        buf->capacity = new_cap;
    }

    nt_memmove((char *)buf->data + (buf->element_count * buf->element_size),
               elt,
               buf->element_size);
    buf->element_count++;

    return (0);
}
