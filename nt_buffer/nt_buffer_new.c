#include "nt_buffer.h"

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
