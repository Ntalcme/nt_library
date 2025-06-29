#include "nt_fd.h"

/**
 * Write a number in a file
 * @param n The number
 * @param fd The file descriptor
 * @return The number of bytes written (-1 if there has been any error)
 */
ssize_t nt_putnbr_fd(int n, const int fd)
{
    if (n <= MIN_INT)
    {
        return nt_putstr_fd(MIN_INT_STR, fd);
    }

    if (n < 0)
    {
        if (nt_putchar_fd('-', fd) == ERROR_WRITING)
        {
            return (ERROR_WRITING);
        }
        n *= -1;
    }

    if (n > 9)
	{
		if (nt_putnbr_fd(n / 10, fd) == ERROR_WRITING)
        {
            return (ERROR_WRITING);
        }
		return (nt_putchar_fd(nt_itochar(n % 10), fd));
	}
    
	return (nt_putchar_fd(nt_itochar(n), fd));
}