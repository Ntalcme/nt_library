#include "nt_buffer.h"

void nt_buffer_clear(nt_buffer *buf)
{
    if (!buf) return;

    if (buf->destructor && buf->data) {
        for (size_t i = 0; i < buf->len; i++) {
            buf->destructor((char *)buf->data + (i * buf->element_size));
        }
    }
    buf->len = 0;
}