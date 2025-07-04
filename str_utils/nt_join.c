#include "nt_str_utils.h"

static int add_string(nt_buffer *buf, char *str)
{
    size_t new_len;
    size_t new_cap;
    char *new_data;
    size_t str_len;

    if (!buf || !str)
        return (1);
    if (buf->element_size != sizeof(char))
        return (1);

    str_len = nt_strlen(str);
    new_len = buf->element_count + str_len;

    if (new_len >= buf->capacity)
    {
        new_cap = buf->capacity ? buf->capacity * 2 : 4;
        while (new_len > new_cap)
        {
            new_cap *= 2;
        }
        new_data = realloc(buf->data, new_cap * buf->element_size);
        if (!new_data)
            return (1);

        buf->data = new_data;
        buf->capacity = new_cap;
    }

    nt_memmove((char *)buf->data + buf->element_count, str, str_len);

    buf->element_count = new_len;
    return (0);
}

char *nt_join(nt_buffer *buf, const char sep)
{
    nt_buffer str;
    char *tmp;
    size_t i;
    char *res;

    if (!buf || !buf->data || buf->element_count == 0)
        return (NULL);
    if (nt_buffer_init(&str, 32, sizeof(char), NULL))
        return (NULL);

    for (i = 0; i < buf->element_count - 1; i++)
    {
        tmp = *(char **)nt_buffer_get(buf, i);
        if (!tmp)
            return (NULL);

        if (add_string(&str, tmp))
            return (NULL);
        if (i < buf->element_count - 2)
            if (nt_buffer_add(&str, &sep))
                return (NULL);
    }

    if (nt_buffer_add(&str, &GLOBAL_NULL_CHAR))
    {
        nt_buffer_free(&str);
        return (NULL);
    }

    res = nt_strdup(str.data);
    nt_buffer_free(&str);
    if (!res)
        return (NULL);
    return (res);
}
