#include <nt_library/nt_buffer.h>

/**
 * Frees all datas of the buffer and free the buffer itself
 * @param buf_ptr The pointer of the buffer's pointer
 */
void nt_buffer_delete(nt_buffer **buf_ptr)
{
    if (!buf_ptr)
        return;
    if (!*buf_ptr)
        return;

    nt_buffer_free(*buf_ptr);
    free(*buf_ptr);
    *buf_ptr = NULL;
}
