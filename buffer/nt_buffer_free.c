# include "nt_buffer.h"


void nt_buffer_free(nt_buffer *buf) 
{
    size_t i;

    if (!buf) return;

    if (buf->data) 
    {
        if (buf->destructor) 
        {
            for (i = 0; i < buf->len; i++) 
            {
                buf->destructor((char *)buf->data + (i * buf->element_size));
            }
        }
        free(buf->data);
        buf->data = NULL;
    }
    buf->len = 0;
    buf->capacity = 0;
    buf->destructor = NULL;
}
