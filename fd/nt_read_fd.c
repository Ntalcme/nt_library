#include "nt_fd.h"
#include <stdlib.h>

char *nt_read_line(const int fd)
{
    char *line;
    char *tmp;
    char c;
    size_t i;
    size_t bufsize;
    ssize_t n;

    if (fd < 0) return (NULL);

    bufsize = 128;
    line = malloc(sizeof(char) * bufsize);

    if (!line) return (NULL);
    
    i = 0;
    n = read(fd, &c, 1);
    while (n == 1)               
    {
        if (c == '\n') break;

        if (i+1 >= bufsize)
        {
            bufsize *= 2;
            tmp = realloc(line, sizeof(char) * bufsize);
            if (!tmp) 
            { 
                free(line); 
                return (NULL); 
            }
            line = tmp;
        }
        line[i++] = c;
        n = read(fd, &c, 1);
    }

    if (n == -1 || (i == 0 && n == 0)) 
    {
        free(line);
        return (NULL);
    }
    line[i] = '\0';
    return line;
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