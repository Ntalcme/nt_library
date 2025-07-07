#include "libnt/nt_str_utils.h"
#include "nt_str_utils_internal.h"

static int add_string(nt_buffer *buf, const char *str)
{
    size_t new_len;
    size_t new_cap;
    char  *new_data;
    size_t str_len;

    if (!buf || !str)
        return (1);
    if (nt_buffer_get_element_size(buf) != sizeof(char))
        return (1);

    str_len = nt_strlen(str);
    new_len = nt_buffer_get_count(buf) + str_len;

    if (new_len >= nt_buffer_get_capacity(buf))
    {
        new_cap = nt_buffer_get_capacity(buf) ? nt_buffer_get_capacity(buf) * 2 : 4;
        while (new_len > new_cap)
        {
            new_cap *= 2;
        }
        new_data = realloc(nt_buffer_get_data(buf), new_cap * nt_buffer_get_element_size(buf));
        if (!new_data)
            return (1);

        nt_buffer_set_data(buf, new_data);
        nt_buffer_set_capacity(buf, new_cap);
    }

    nt_memmove((char *)nt_buffer_get_data(buf) + nt_buffer_get_count(buf), str, str_len);

    nt_buffer_set_count(buf, new_len);
    return (0);
}

char *nt_join(nt_buffer *buf, const char sep)
{
    nt_buffer  *str;
    const char *tmp;
    size_t      i;
    char       *res;

    if (!nt_buffer_get_data(buf) || nt_buffer_get_count(buf) == 0)
        return (NULL);

    str = nt_buffer_new(32, sizeof(char), NULL);
    if (!str)
        return (NULL);

    for (i = 0; i < nt_buffer_get_count(buf) - 1; i++)
    {
        tmp = *nt_buffer_get_element_as(char **, buf, i);
        if (!tmp)
        {
            nt_buffer_delete(&str);
            return (NULL);
        }

        if (add_string(str, tmp))
            return (NULL);
        if (i < nt_buffer_get_count(buf) - 2)
            if (nt_buffer_add(str, &sep))
                return (NULL);
    }

    if (nt_buffer_add(str, &GLOBAL_NULL_CHAR))
    {
        nt_buffer_delete(str);
        return (NULL);
    }

    res = nt_strdup(nt_buffer_get_data(str));
    nt_buffer_delete(&str);
    if (!res)
        return (NULL);
    return (res);
}
