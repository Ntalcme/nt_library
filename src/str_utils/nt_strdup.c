#include "libnt/nt_str_utils.h"
#include "nt_str_utils_internal.h"

/**
 * Duplicate a character string
 * @param str The character string's pointer
 * @return A pointer to the new character string
 */
char *nt_strdup(const char *str)
{
    char  *res;
    size_t reslen;
    size_t i;

    if (!str)
        return (NULL);

    reslen = nt_strlen(str);
    res = malloc(sizeof(char) * (reslen + 1));

    if (!res)
        return (NULL);

    i = 0;
    while (i < reslen)
    {
        res[i] = str[i];
        i++;
    }
    res[i] = GLOBAL_NULL_CHAR;

    return (res);
}
