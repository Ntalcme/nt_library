# nt_library - My personal library for C

**nt_library** is my custom library for C including differents features.

| Project | nt_library                 |
|:--------|---------------------------:|
| Open    | 2025-06-28                 |
| Closed  | *Not closed yet*           |


### Summary
[C Version](#c-version)  
[Compatibility](#compatibility)
[Features](#features)  
[Local Compilation & Linking](#local-compilation--linking)  
[System-Wide Installation](#system-wide-installation-make-install)  
[Usage](#usage)  
[System-Wide Uninstallation](#system-wide-uninstallation-make-uninstall)  
[License](#license)  
[Author](#author)

## C Version

This library is compatible with C99 and its next versions.

## Compatibility

This project uses POSIX system calls (such as `read`),
making it compatible with Unix-like operating systems including:

- Linux
- macOS
- BSD variants (FreeBSD, OpenBSD, NetBSD)
- Other POSIX-compliant systems

*Note: This project is not natively compatible with Windows.*

## Features

- Conversion
    - `nt_itochar` - Converts a digit to its character representation.
    - `nt_itoa` - Converts an integer to its string representation.
    - `nt_itohex` - Converts an integer to its hexadecimal string representation.
- FD
    - `nt_putchar` - Writes a character to the given file descriptor.
    - `nt_putnbr` - Writes a number to the given file descriptor.
    - `nt_putstr`- Writes a string to the given file descriptor.
    - `nt_read_line` - Reads a single line from the given file descriptor *(excluding the character "\n")*.
    - `nt_read_lines` - Reads all lines from the given file descriptor using `nt_read_line`.
- mem
    - `nt_free_char_ptr` - Destructor function for `nt_buffer` struct which stocks `char *` type.
    - `nt_memmove` - Custom version of `memmove` function.
- `nt_buffer` - A custom generic buffer structure for dynamic array management, supporting elements of any type and custom destructor functions for memory safety.
- `nt_printf` - Minimalist version of C printf function.
- String utils
    - `nt_strdup` - Duplicates a string.
    - `nt_strlen` - Returns the length of a string.
    - `nt_parse` - Simple function to parse a character string.

## Local Compilation & Linking

1. Clone this repository:
```bash
git clone https://github.com/Ntalcme/nt_library.git
```

2. Navigate into the project directory:
```bash
cd nt_library
```

3. Build the static library using `make`:
```bash
make
```
This will generate a static library file named `libnt.a` in the project directory.

4. Include the library in your project:
    - Copy the `libnt.a` file to your project's directory or link it during compilation.
    - Include the `libnt.h` header file in your C source files.  

Example compilation in your project:
```bash
gcc your_program.c -I./path_to_nt_library_headers -L./path_to_nt_library_binary -lnt -o your_program
```

## System-Wide Installation (`make install`)
First, clone the repository and navigate into its directory. 

Install the library *(may require `sudo` privileges)* :
```bash
make install
```
This will generate a static library file named `libnt.a` in `/usr/local/lib` and its headers in `/usr/local/include/libnt`.  

Include the library in your C files:
```C
#include <libnt/libnt.h>
```
Example compilation in your project:
```bash
gcc your_program.c -I/usr/local/include/libnt -L/usr/local/lib -lnt -o your_program
```

## Usage
Once you've linked the `libnt.a` library, you can use all of its functions in your project.  
```C
#include <libnt/libnt.h> /* Or #include "libnt.h" if linking locally without system install */

int main(void)
{
    char message[8] = "Ntalcme";

    nt_printf("Hello, World!\n");
    nt_printf("My creator %s has %d letters in his nickname.\n", message, nt_strlen(message));
}
```
Output:
```bash
Hello, World!
My creator Ntalcme has 6 letters in his nickname.
```

You also can include only some parts of the library.  
Example:
```C
#include <libnt/conversion/conversion.h> /* or #include "conversion/conversion.h" if linking locally without system install */
```

## System-Wide Uninstallation (`make uninstall`)

1. Navigate into the project directory:
```bash
cd nt_library
```

Uninstall the library *(may require `sudo` privileges)* :
```bash
make uninstall
```
This command removes `libnt.a` from `/usr/local/lib` and the `libnt` header directory from `/usr/local/include`.

## License

This project is licensed under the BSD-3-Clause License - see the [LICENSE](./LICENSE) file for details.

## Author
[Ntalcme](https://github.com/Ntalcme)
