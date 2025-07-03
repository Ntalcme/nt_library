#ifndef NT_MEM_H
#define NT_MEM_H

# include <stdlib.h>

void *nt_memmove(void *dst, const void *src, size_t num_bytes);
void nt_free_char_ptr(void *elt_ptr);


#endif