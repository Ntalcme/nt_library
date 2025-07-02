#include "nt_str_utils.h"

DEFINE_BUFFER_TYPE(char, char)
DEFINE_BUFFER_TYPE(char *, ptr_char)

static void nt_parse_fail(nt_ptr_char_buffer *buf, nt_char_buffer *str)
{
    nt_ptr_char_buffer_delete(buf);
    nt_char_buffer_free(str);
}

nt_ptr_char_buffer *nt_parse(const char *str, const char sep)
{
    nt_char_buffer tmp;
    nt_ptr_char_buffer *res;
    size_t i = 0;

    if (!nt_char_buffer_init(&tmp, 16, NULL)) 
    {
        return (NULL);
    }

    res = nt_ptr_char_buffer_new(16, free);
    if (!res)
    {
        nt_char_buffer_free(&tmp);
        return (NULL);
    }

    while (str[i]) 
    {
        if (str[i] != sep) 
        {
            if (!nt_char_buffer_add(&tmp, str[i++])) 
            {
                nt_parse_fail(res, &tmp);
                return (NULL);
            }
        } 
        
        else 
        {
            if (!nt_char_buffer_add(&tmp, '\0') || !nt_ptr_char_buffer_add(res, nt_strdup(tmp.data))) 
            {
                nt_parse_fail(res, &tmp);
                return (NULL);
            }
            nt_char_buffer_reset(&tmp);
            i++;
        }
    }

    if (tmp.len > 0) 
    {
        if (!nt_char_buffer_add(&tmp, '\0') || !nt_ptr_char_buffer_add(res, nt_strdup(tmp.data))) 
        {
            nt_parse_fail(res, &tmp);
            return (NULL);
        }
    }

    if (!nt_ptr_char_buffer_add(res, NULL)) 
    {
        nt_parse_fail(res, &tmp);
        return (NULL);
    }

    nt_char_buffer_free(&tmp);
    return (res);
}
