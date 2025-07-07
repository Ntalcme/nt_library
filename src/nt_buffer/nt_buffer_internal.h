#ifndef NT_BUFFER_INTERNAL_H
#define NT_BUFFER_INTERNAL_H

#include <stddef.h>

struct nt_buffer
{
    void  *data;
    size_t element_count;
    size_t capacity;
    size_t element_size;
    void (*destructor)(void *);
};

int nt_buffer_set_data(nt_buffer *buf, void *new_value);
int nt_buffer_set_count(nt_buffer *buf, size_t new_value);
int nt_buffer_set_capacity(nt_buffer *buf, size_t new_value);

#endif
