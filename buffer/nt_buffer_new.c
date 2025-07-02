#include "nt_buffer.h"


nt_buffer *nt_buffer_new(size_t capacity, size_t element_size, void (*destructor)(void*))
{
    nt_buffer *res;

    res = malloc(sizeof(nt_buffer));
    if (!res) return (NULL);

    if (nt_buffer_init(res, capacity, element_size, destructor))
    {
        free(res);
        return (NULL);
    }
    return (res);
}
