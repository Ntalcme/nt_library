# include "nt_buffer.h"

/**
 * Init a buffer with a start capacity of data, 
 * the bytes' size of elements that will be stocked in it 
 * and a pointer of a destructor function (NULL if not needed)
 * @param buf The buffer's pointer
 * @param capacity The initial capacity
 * @param element_size The bytes' size of the future stocked elements (ex: 1 for char type)
 * @param destructor An appropriate destructor function pointer (NULL if not needed))
 * @return 1 if failed, 0 if success
 */
int nt_buffer_init(nt_buffer *buf, size_t capacity, size_t element_size, void (*destructor)(void*))
{
    if (!buf || element_size == 0) return (1);

    buf->data = NULL;
    if (capacity > 0)
    {
        buf->data = malloc(element_size * capacity);
        if (!buf->data) return (1);
    }
    buf->capacity = capacity;
    buf->len = 0;
    buf->element_size = element_size;
    buf->destructor = destructor;
    return (0);
}
