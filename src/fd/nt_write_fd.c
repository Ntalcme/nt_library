#include <libnt/nt_fd.h>

/**
 * Write a character in a file
 * @param c The character
 * @param fd The file descriptor
 * @return The number of byte written (-1 if there has been any error)
 */
ssize_t nt_putchar_fd(const char c, const int fd)
{
    return write(fd, &c, 1);
}

/**
 * Write a number in a file
 * @param n The number
 * @param fd The file descriptor
 * @return The number of bytes written (-1 if there has been any error)
 */
ssize_t nt_putnbr_fd(long long n, int fd)
{
    char               buffer[21];
    char              *ptr;
    unsigned long long abs;
    ssize_t            written;

    ptr = &buffer[20];
    *ptr = '\0';

    if (n < 0)
        abs = (unsigned long long)(-(n + 1)) + 1;
    else
        abs = (unsigned long long)n;

    do
    {
        *--ptr = '0' + (abs % 10);
        abs /= 10;
    } while (abs > 0);

    if (n < 0)
        *--ptr = '-';

    return write(fd, ptr, &buffer[20] - ptr);
}

/**
 * Write a character string in a file
 * @param str The character string's pointer
 * @param fd The file descriptor
 * @return The number of bytes written (-1 if there has been any error)
 */
ssize_t nt_putstr_fd(const char *str, const int fd)
{
    if (!str)
        return (ERROR_WRITING);
    return write(fd, str, nt_strlen(str));
}
