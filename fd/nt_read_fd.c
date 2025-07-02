#include "nt_fd.h"
#include <stdlib.h>

char *nt_read_line(const int fd)
{
    nt_buffer line;
    char c;
    ssize_t n;
    char *res;
    char null_char;

    if (fd < 0) return (NULL);

    if (nt_buffer_init(&line, 128, sizeof(char), NULL)) return (NULL);

    n = read(fd, &c, 1);
    while (n == 1)               
    {
        if (c == '\n') break;
        if (nt_buffer_add(&line, &c))
        {
            nt_buffer_free(&line);
            return (NULL);
        } 
        n = read(fd, &c, 1);
    }

    if (n == -1 || (line.len == 0 && n == 0)) 
    {
        nt_buffer_free(&line);
        return (NULL);
    }
    null_char = '\0';
    if (nt_buffer_add(&line, &null_char))
    {
            nt_buffer_free(&line);
            return (NULL);
    }

    res = nt_strdup(line.data);
    nt_buffer_free(&line);
    return (res);
}

nt_buffer *nt_read_lines(const int fd)
{
    nt_buffer *lines;
    char *line;

    lines = nt_buffer_new(16, sizeof(char *), nt_free_char_ptr);
    if (!lines) return (NULL);

    while ((line = nt_read_line(fd)) != NULL)
    {
        if (nt_buffer_add(lines, line))
        {
            nt_buffer_delete(lines); 
            return (NULL);
        }
    }

    if (nt_buffer_add(lines, NULL))
    {
        nt_buffer_delete(lines); 
        return (NULL);
    }

    return (lines);
}
