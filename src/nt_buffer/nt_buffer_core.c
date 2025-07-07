#include "libnt/nt_buffer.h"
#include "nt_buffer_internal.h"

/**
 * Init a buffer with a start capacity of data,
 * the bytes' size of elements that will be stocked in it
 * and a pointer of a destructor function (NULL if not needed)
 * @param buf The buffer's pointer
 * @param capacity The initial capacity
 * @param element_size The bytes' size of the future stocked elements (ex: 1 for
 * char type)
 * @param destructor An appropriate destructor function pointer (NULL if not
 * needed))
 * @return 1 if failed, 0 if success
 */
static int
nt_buffer_init(nt_buffer *buf, size_t capacity, size_t element_size, void (*destructor)(void *))
{
    if (!buf || element_size == 0)
        return (1);

    buf->data = NULL;
    if (capacity > 0)
    {
        buf->data = malloc(element_size * capacity);
        if (!buf->data)
            return (1);
    }
    buf->capacity = capacity;
    buf->element_count = 0;
    buf->element_size = element_size;
    buf->destructor = destructor;
    return (0);
}

/**
 * Allocate and init a nt_buffer struct with specified params
 * @param capacity The initial capacity
 * @param element_size The bytes' size of the future stocked elements (ex: 1 for
 * char type)
 * @param destructor An appropriate destructor function pointer (NULL if not
 * needed)
 * @return The new nt_buffer's pointer (NULL if any error)
 */
nt_buffer *nt_buffer_new(size_t capacity, size_t element_size, void (*destructor)(void *))
{
    nt_buffer *res;

    res = malloc(sizeof(nt_buffer));
    if (!res)
        return (NULL);

    if (nt_buffer_init(res, capacity, element_size, destructor))
    {
        free(res);
        return (NULL);
    }
    return (res);
}

/**
 * Frees all dynamically allocated memory within the buffer and resets its state
 * to empty The buffer itself is not freed by this function
 * @param buf The buffer's pointer
 */
static void nt_buffer_free(nt_buffer *buf)
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

/**
 * Frees all datas of the buffer and free the buffer itself
 * @param buf_ptr The pointer of the buffer's pointer
 */
void nt_buffer_delete(nt_buffer **buf_ptr)
{
    if (!buf_ptr)
        return;
    if (!*buf_ptr)
        return;

    nt_buffer_free(*buf_ptr);
    free(*buf_ptr);
    *buf_ptr = NULL;
}

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

/**
 * Remove an element of the nt_buffer at an index
 * Elements after the removed one are shifted to fill the gap
 * @param buf The buffer's pointer
 * @param i The index
 */
void nt_buffer_remove(nt_buffer *buf, size_t i)
{
    size_t bytes_to_move;

    if (!buf || !buf->data || i >= buf->element_count)
        return;

    if (buf->destructor)
    {
        buf->destructor((char *)buf->data + (i * buf->element_size));
    }

    bytes_to_move = (buf->element_count - 1 - i) * buf->element_size;
    nt_memmove((char *)buf->data + (i * buf->element_size),
               (char *)buf->data + ((i + 1) * buf->element_size),
               bytes_to_move);

    buf->element_count--;
}

/**
 * Reallocs only the necessary memory for the buffer's data
 * @param buf The buffer's pointer
 * @return 1 if failed, 0 if success
 */
int nt_buffer_shrink_to_fit(nt_buffer *buf)
{
    void *new_data;

    if (!buf || !buf->data || buf->element_count == buf->capacity)
        return (0);

    if (buf->element_count == 0)
    {
        free(buf->data);
        buf->data = NULL;
        buf->capacity = 0;
        return (0);
    }

    new_data = realloc(buf->data, buf->element_count * buf->element_size);

    if (!new_data)
        return (1);
    buf->data = new_data;
    buf->capacity = buf->element_count;

    return (0);
}
