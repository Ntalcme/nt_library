#ifndef NT_BUFFER_INTERNAL_H
#define NT_BIFFER_INTERNAL_H

#include <stddef.h>

struct nt_buffer
{
    void  *data;
    size_t element_count;
    size_t capacity;
    size_t element_size;
    void (*destructor)(void *);
};

#endif
