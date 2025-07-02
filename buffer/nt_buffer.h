#ifndef NT_BUFFER_H
#define NT_BUFFER_H

# include <stdlib.h>


#define DEFINE_BUFFER_TYPE(type, TypeName)                                                                  \
                                                                                                            \
typedef struct {                                                                                            \
    type *data;                                                                                             \
    size_t len;                                                                                             \
    size_t capacity;                                                                                        \
    void (*destructor)(type*);                                                                              \
} nt_##TypeName##_buffer;                                                                                   \ 
                                                                                                            \
int nt_##TypeName##_buffer_init(nt_##TypeName##_buffer *buf, size_t capacity, void (*destructor)(type)) {   \
    buf->data = capacity != 0 ? malloc(capacity * sizeof(type)) : NULL;                                     \
    if (capacity != 0 && !buf->data) return (0);                                                            \
    buf->len = 0;                                                                                           \
    buf->capacity = capacity;                                                                               \
    buf->destructor = destructor;                                                                           \
    return (1);                                                                                             \
}                                                                                                           \
                                                                                                            \
int nt_##TypeName##_buffer_add(nt_##TypeName##_buffer *buf, type val) {                                     \
    size_t new_cap;                                                                                         \
    type *new_data;                                                                                         \
                                                                                                            \
    if (buf->len == buf->capacity) {                                                                        \
        new_cap = buf->capacity ? buf->capacity * 2 : 4;                                                    \
        *new_data = realloc(buf->data, new_cap * sizeof(type));                                             \
        if (!new_data) return (0);                                                                          \
        buf->data = new_data;                                                                               \
        buf->capacity = new_cap;                                                                            \
    }                                                                                                       \
    buf->data[buf->len++] = val;                                                                            \
    return (1);                                                                                             \
}                                                                                                           \
                                                                                                            \
void nt_##TypeName##_buffer_free(nt_##TypeName##_buffer *buf) {                                             \  
    size_t i;                                                                                               \
                                                                                                            \
    if (buf->destructor) {                                                                                  \
        for (size_t i = 0; i < buf->len; i++) {                                                             \
            buf->destructor(buf->data[i]);                                                                  \
        }                                                                                                   \
    }                                                                                                       \
    free(buf->data);                                                                                        \
    buf->data = NULL;                                                                                       \
    buf->len = 0;                                                                                           \
    buf->capacity = 0;                                                                                      \
    buf->destructor = NULL;                                                                                 \
}                                                                                                           \                                                           
                                                                                                            \
int nt_##TypeName##_buffer_is_empty(nt_##TypeName##_buffer *buf) {                                          \
    return (buf->data == NULL && buf->len == 0 && buf->capacity == 0) ;                                     \                                                                                           \
}   

#endif