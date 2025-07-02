#include "nt_buffer.h"

void nt_buffer_delete(nt_buffer **buf_ptr)
{
    if (!buf_ptr) return;
    if (!*buf_ptr) return;
    
    nt_buffer_free(*buf_ptr);
    free(*buf_ptr);
    *buf_ptr = NULL;
}