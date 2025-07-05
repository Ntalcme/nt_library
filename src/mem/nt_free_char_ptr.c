#include <libnt/nt_mem.h>

void nt_free_char_ptr(void *elt_ptr)
{
    char **str_to_free;

    str_to_free = (char **)elt_ptr;
    if (str_to_free && *str_to_free)
    {
        free(*str_to_free);
        *str_to_free = NULL;
    }
}
