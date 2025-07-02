#include "nt_fd.h"
#include <stdlib.h>

char *nt_read_line(const int fd)
{
    nt_char_buffer line;
    char c;
    ssize_t n;

    if (fd < 0) return (NULL);

    if (!nt_char_buffer_init(&line, 128, NULL)) return (NULL);

    n = read(fd, &c, 1);
    while (n == 1)               
    {
        if (c == '\n') break;
        if (!nt_char_buffer_add(&line, c))
        {
            nt_char_buffer_free(&line);
            return (NULL);
        } 
        n = read(fd, &c, 1);
    }

    if (n == -1 || (line.len == 0 && n == 0)) 
    {
        nt_char_buffer_free(&line);
        return (NULL);
    }
    if (!nt_char_buffer_add(&line, '\0'))
    {
            nt_char_buffer_free(&line);
            return (NULL);
    }
    return line.data;
}

nt_ptr_char_buffer *nt_read_lines(const int fd)
{
    nt_ptr_char_buffer *lines;
    char *line;

    lines = nt_ptr_char_buffer_new(16, nt_ptr_char_buffer_free_wrapper);
    if (!lines) return (NULL);

    while ((line = nt_read_line(fd)) != NULL)
    {
        if (!nt_ptr_char_buffer_add(lines, line))
        {
            nt_ptr_char_buffer_delete(lines); 
            return (NULL);
        }
    }

    if (!nt_ptr_char_buffer_add(lines, NULL))
    {
        nt_ptr_char_buffer_delete(lines); 
        return (NULL);
    }

    return (lines);
}
