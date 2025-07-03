#ifndef NT_FD_H
#define NT_FD_H

#define ERROR_WRITING -1

# include <unistd.h>
# include "../str_utils/nt_str_utils.h"
# include "../conversion/nt_conversion.h"
# include "../nt_buffer/nt_buffer.h"

ssize_t nt_putchar_fd(const char c, const int fd);
ssize_t nt_putstr_fd(const char *str, const int fd);
ssize_t nt_putnbr_fd(int n, const int fd);
char *nt_read_line(const int fd);
nt_buffer *nt_read_lines(const int fd);

#endif
