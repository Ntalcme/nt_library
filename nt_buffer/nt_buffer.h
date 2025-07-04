#ifndef NT_BUFFER_H
#define NT_BUFFER_H

#include "../mem/nt_mem.h"
#include <stdlib.h>

typedef struct
{
    void  *data;
    size_t element_count;
    size_t capacity;
    size_t element_size;
    void (*destructor)(void *);
} nt_buffer;

int nt_buffer_init(nt_buffer *buf,
                   size_t     capacity,
                   size_t     element_size,
                   void (*destructor)(void *));

int nt_buffer_add(nt_buffer *buf, const void *elt);

void *nt_buffer_get(nt_buffer *buf, size_t i);

void nt_buffer_remove(nt_buffer *buf, size_t i);

void nt_buffer_free(nt_buffer *buf);

void nt_buffer_clear(nt_buffer *buf);

nt_buffer *nt_buffer_new(size_t capacity, size_t element_size, void (*destructor)(void *));

void nt_buffer_delete(nt_buffer **buf_ptr);

int nt_buffer_shrink_to_fit(nt_buffer *buf);

#endif
