#include "libnt/nt_str_utils.h"
#include "nt_str_utils_internal.h"

static void nt_parse_fail(nt_buffer *buf, nt_buffer *str)
{
    if (buf)
        nt_buffer_delete(&buf);
    if (str)
        nt_buffer_delete(&str);
}

static int manage_add_str(nt_buffer *buf, nt_buffer *str)
{
    const char *tmp;

    if (!buf || !str)
        return (1);

    if (nt_buffer_get_count(str) == 0)
    {
        if (nt_buffer_add(buf, &GLOBAL_EMPTY_STRING))
        {
            nt_parse_fail(buf, str);
            return (1);
        }
        return (0);
    }

    if (nt_buffer_add(str, &GLOBAL_NULL_CHAR))
    {
        nt_parse_fail(buf, str);
        return (1);
    }

    tmp = nt_strdup((const char *)nt_buffer_get_data(str));
    if (!tmp)
    {
        nt_parse_fail(buf, str);
        return (1);
    }

    if (nt_buffer_add(buf, &tmp))
    {
        free(tmp);
        nt_parse_fail(buf, str);
        return (1);
    }

    return (0);
}

/**
 * Parse a character string with the given separator
 * @param str The character string
 * @param sep A separator
 * @return A pointer of a nt_buffer struct containing the parsed string
 */
nt_buffer *nt_parse(const char *str, const char sep)
{
    nt_buffer *tmp;
    nt_buffer *res;
    size_t     i;

    tmp = nt_buffer_new(16, sizeof(char), NULL);
    if (!tmp)
    {
        return (NULL);
    }

    res = nt_buffer_new(16, sizeof(char *), nt_free_char_ptr);
    if (!res)
    {
        nt_buffer_delete(&tmp);
        return (NULL);
    }

    i = 0;
    while (str[i])
    {
        if (str[i] != sep)
        {
            if (nt_buffer_add(tmp, &str[i++]))
            {
                nt_parse_fail(res, tmp);
                return (NULL);
            }
        }

        else
        {
            if (manage_add_str(res, tmp))
            {
                nt_parse_fail(res, tmp);
                return (NULL);
            }
            nt_buffer_clear(tmp);
            i++;
        }
    }

    if (nt_buffer_get_count(tmp) > 0)
    {
        if (manage_add_str(res, tmp))
        {
            nt_parse_fail(res, tmp);
            return (NULL);
        }
    }

    if (nt_buffer_add(res, &GLOBAL_NULL_PTR))
    {
        nt_parse_fail(res, tmp);
        return (NULL);
    }

    nt_buffer_delete(&tmp);

    if (nt_buffer_shrink_to_fit(res))
    {
        nt_buffer_delete(&res);
        return (NULL);
    }

    return (res);
}
