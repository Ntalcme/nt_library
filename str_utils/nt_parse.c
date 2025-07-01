#include "nt_str_utils.h"

static void free_buffer(char **buffer, size_t count)
{
    while (count > 0)
    {
        free(buffer[--count]);
    }
    free(buffer);
}

char **nt_parse(const char *str, const char sep)
{
    size_t i;
    size_t j;
    char **res;
    char **tmp_buf;
    nt_char_buffer tmp;
    size_t bufsize;
    

    if (!str) return (NULL);
    if (!nt_char_buffer_init(&tmp, 0)) return (NULL);

    bufsize = 20;
    res = malloc(sizeof(char*) * bufsize);
    if (!res) return (NULL);

    i = 0;
    j = 0;
    res[j] = NULL;
    while (str[i])
    {
        if (str[i] != sep)
        {
            if (!nt_char_buffer_add_char(&tmp, str[i]))
            {
                free(tmp.data);
                return (NULL);
            }
        }

        else
        {
            if (j+1 >= bufsize)
            {
                bufsize *= 2;
                tmp_buf = realloc(res, sizeof(char*) * bufsize);
                if (!tmp_buf) 
                {
                    free(tmp.data);
                    free_buffer(res, j);
                    return (NULL);
                }
            
                res = tmp_buf;
            }
            res[j++] = tmp.data;
            if (!nt_char_buffer_init(&tmp, 0)) return (NULL);
        }
        i++;
    }
    return res;
}