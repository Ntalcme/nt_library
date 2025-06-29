#include "nt_fd.h"

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