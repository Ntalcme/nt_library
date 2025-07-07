#ifndef NT_BUFFER_H
#define NT_BUFFER_H

#include "nt_mem.h"
#include <stdlib.h>

typedef struct nt_buffer nt_buffer;

nt_buffer *nt_buffer_new(size_t capacity, size_t element_size, void (*destructor)(void *));
void       nt_buffer_delete(nt_buffer **buf_ptr);
int        nt_buffer_add(nt_buffer *buf, const void *elt);
void       nt_buffer_remove(nt_buffer *buf, size_t i);
void       nt_buffer_clear(nt_buffer *buf);
int        nt_buffer_shrink_to_fit(nt_buffer *buf);

const void *nt_buffer_get_data(const nt_buffer *buf);
size_t      nt_buffer_get_count(const nt_buffer *buf);
size_t      nt_buffer_get_element_size(const nt_buffer *buf);
size_t      nt_buffer_get_capacity(const nt_buffer *buf);

#define nt_buffer_get_element_as(type, buf, i) ((const type *)nt_buffer_get_element(buf, i))

#endif
