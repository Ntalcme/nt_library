# nt_library - My personal library for C

**nt_library** is  my custom library for C including differents features.

## Features

- Conversion
    - `itochar` - Converts a digit to its character representation.
    - `itoa` - Converts an integer to its string representation.
    - `itohex` - Converts an integer to its hexadecimal string representation.
- FD
    - `putchar` - Writes a character to the given file descriptor.
    - `putnbr` - Writes a number to the given file descriptor.
    - `putstr`- Writes a string to the given file descriptor.
    - `read_line` - Reads a single line from the given file descriptor *(ommissing the character "\n")*.
    - `read_lines` - Reads all lines from the given file descriptor using `read_line`.
- String utils
    - `strdup` - Duplicates a string.
    - `strlen` - Returns the length of a string.