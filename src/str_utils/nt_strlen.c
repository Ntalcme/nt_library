#include <nt_library/nt_str_utils.h>

/**
 * Return the len of a character string
 * @param str The character string's pointer
 * @return The number of bytes of str
 */
size_t nt_strlen(const char *str)
{
    size_t res;

    res = 0;
    while (str[res])
    {
        res++;
    }
    return (res);
}
