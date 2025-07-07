#include <libnt/nt_fd.h>
#include <stdlib.h>

char *nt_read_line(const int fd)
{
    nt_buffer *line;
    char       c;
    ssize_t    n;
    char      *res;

    if (fd < 0)
        return (NULL);

    line = nt_buffer_new(128, sizeof(char), NULL);
    if (!line)
        return (NULL);

    n = read(fd, &c, 1);
    while (n == 1)
    {
        if (c == '\n')
            break;
        if (nt_buffer_add(line, &c))
        {
            nt_buffer_delete(&line);
            return (NULL);
        }
        n = read(fd, &c, 1);
    }

    if (n == -1 || (nt_buffer_get_count(line) == 0 && n == 0))
    {
        nt_buffer_delete(&line);
        return (NULL);
    }
    if (nt_buffer_add(line, &GLOBAL_NULL_CHAR))
    {
        nt_buffer_delete(&line);
        return (NULL);
    }

    res = nt_strdup(nt_buffer_get_data(line));
    nt_buffer_delete(&line);
    if (!res)
        return (NULL);
    return (res);
}

nt_buffer *nt_read_lines(const int fd)
{
    nt_buffer *lines;
    char      *line;

    lines = nt_buffer_new(16, sizeof(char *), nt_free_char_ptr);
    if (!lines)
        return (NULL);

    while ((line = nt_read_line(fd)) != NULL)
    {
        if (nt_buffer_add(lines, &line))
        {
            free(line);
            nt_buffer_delete(&lines);
            return (NULL);
        }
    }

    if (nt_buffer_add(lines, &GLOBAL_NULL_PTR))
    {
        nt_buffer_delete(&lines);
        return (NULL);
    }

    if (nt_buffer_shrink_to_fit(lines))
    {
        nt_buffer_delete(&lines);
        return (NULL);
    }

    return (lines);
}
