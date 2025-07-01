#include "nt_fd.h"
#include <stdlib.h>

char *nt_read_line(const int fd)
{
    nt_char_buffer line;
    char c;
    ssize_t n;

    if (fd < 0) return (NULL);

    if (!nt_char_buffer_init(&line, 1, 128)) return (NULL);

    n = read(fd, &c, 1);
    while (n == 1)               
    {
        if (c == '\n') break;
        if (!nt_char_buffer_add_char(&line, c))
        {
            free(line.data);
            return (NULL);
        } 
        n = read(fd, &c, 1);
    }

    if (n == -1 || (line.len == 0 && n == 0)) 
    {
        free(line.data);
        return (NULL);
    }
    return line.data;
}

static void free_buffer(char **buffer, size_t count)
{
    while (count > 0)
    {
        free(buffer[--count]);
    }
    free(buffer);
}

char **nt_read_lines(const int fd)
{
    char **lines;
    char **tmp;
    char *line;
    size_t bufsize;
    size_t i;

    bufsize = 20;
    lines = malloc(sizeof(char*) * bufsize);

    if (!lines) return (NULL);

    i = 0;
    line = nt_read_line(fd);
    while (line != NULL)               
    {

        if (i+1 >= bufsize)
        {
            bufsize *= 2;
            tmp = realloc(lines, sizeof(char*) * bufsize);
            if (!tmp) 
            {
                free(line);
                free_buffer(lines, i);
                return (NULL);
            }
           
            lines = tmp;
        }
        lines[i++] = line;
        line = nt_read_line(fd);
    }
    lines[i] = NULL;
    return (lines);
}
