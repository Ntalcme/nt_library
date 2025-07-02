#include "nt_str_utils.h"

static void nt_parse_fail(nt_buffer *buf, nt_buffer *str)
{
    if (buf) nt_buffer_delete(&buf);
    if (str) nt_buffer_free(str);
}

nt_buffer *nt_parse(const char *str, const char sep)
{
    nt_buffer tmp;
    nt_buffer *res;
    size_t i;

    if (nt_buffer_init(&tmp, 16, sizeof(char), NULL)) 
    {
        return (NULL);
    }

    res = nt_buffer_new(16, sizeof(char *), nt_free_char_ptr);
    if (!res)
    {
        nt_char_buffer_free(&tmp);
        return (NULL);
    }

    i = 0;
    while (str[i]) 
    {
        if (str[i] != sep) 
        {
            if (nt_buffer_add(&tmp, &str[i++])) 
            {
                nt_parse_fail(res, &tmp);
                return (NULL);
            }
        } 
        
        else 
        {
            if (nt_buffer_add(&tmp, &GLOBAL_NULL_CHAR) || nt_buffer_add(res, nt_strdup(tmp.data))) 
            {
                nt_parse_fail(res, &tmp);
                return (NULL);
            }
            nt_buffer_clear(&tmp);
            i++;
        }
    }

    if (tmp.len > 0) 
    {
        if (nt_buffer_add(&tmp, &GLOBAL_NULL_CHAR) || nt_buffer_add(res, nt_strdup(tmp.data))) 
        {
            nt_parse_fail(res, &tmp);
            return (NULL);
        }
    }

    if (nt_buffer_add(res, NULL)) 
    {
        nt_parse_fail(res, &tmp);
        return (NULL);
    }

    nt_buffer_free(&tmp);
    return (res);
}
