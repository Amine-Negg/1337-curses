*This project has been created as part of the 42 curriculum by mohanegg.*

# Libft

## Description

**Libft** is a personal C library built for the 42 / 1337 Common Core curriculum. Its goal is to reimplement a selection of standard C library functions and provide additional utilities for strings, memory, file descriptors, and linked lists. The project introduces low-level memory manipulation, dynamic allocation, pointer arithmetic, function pointers, data structures, and reusable C code.

The library is compiled into a static archive, **`libft.a`**, which can be linked into future C projects.

## Library Description

The project implements **43 functions**, organized into three parts.

### Part 1 — Libc functions (23 functions)

These functions recreate common behaviors from the C standard library and related utilities:

| Category | Functions | Purpose |
| --- | --- | --- |
| Character checks and conversion | `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_toupper`, `ft_tolower` | Classify ASCII characters or change letter case. |
| Strings | `ft_strlen`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr`, `ft_strlcpy`, `ft_strlcat` | Measure, search, compare, and copy or concatenate bounded strings. |
| Memory | `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp` | Initialize, move, search, or compare raw memory. `ft_memmove` supports overlapping regions. |
| Conversion and allocation | `ft_atoi`, `ft_calloc`, `ft_strdup` | Parse an integer, allocate zero-initialized memory, and duplicate a string. |

### Part 2 — Additional functions (11 functions)

| Function | Purpose |
| --- | --- |
| `ft_substr` | Allocate a substring from a given start position and length. |
| `ft_strjoin` | Allocate the concatenation of two strings. |
| `ft_strtrim` | Remove characters from a set at both ends of a string. |
| `ft_split` | Split a string into a NULL-terminated array of strings. |
| `ft_itoa` | Convert an integer to a newly allocated string. |
| `ft_strmapi` | Create a new string by applying a function to each character and its index. |
| `ft_striteri` | Apply a function to each character of an existing string. |
| `ft_putchar_fd` | Write a character to a file descriptor. |
| `ft_putstr_fd` | Write a string to a file descriptor. |
| `ft_putendl_fd` | Write a string followed by a newline to a file descriptor. |
| `ft_putnbr_fd` | Write an integer to a file descriptor. |

### Part 3 — Linked-list functions (9 functions)

The list utilities use the `t_list` structure declared in `libft.h`, with a `void *content` pointer and a `next` pointer.

| Function | Purpose |
| --- | --- |
| `ft_lstnew` | Allocate and initialize a node. |
| `ft_lstadd_front` | Insert a node at the beginning of a list. |
| `ft_lstsize` | Count the nodes in a list. |
| `ft_lstlast` | Return the final node. |
| `ft_lstadd_back` | Append a node to the end of a list. |
| `ft_lstdelone` | Delete one node using a content-deletion callback. |
| `ft_lstclear` | Delete a list and set its head to `NULL`. |
| `ft_lstiter` | Apply a callback to each node's content. |
| `ft_lstmap` | Build a new list from transformed contents, cleaning up on allocation failure. |

## Instructions

### Requirements

- A C compiler (`cc`) and the `make` and `ar` tools.
- No third-party libraries are required to build Libft.

### Compilation

From the project root, run:

```sh
make
```

This compiles the source files using `-Wall -Wextra -Werror` and creates `libft.a` in the project root.

| Command | Action |
| --- | --- |
| `make` or `make all` | Build `libft.a`. |
| `make clean` | Remove object (`.o`) files. |
| `make fclean` | Remove object files and `libft.a`. |
| `make re` | Rebuild the library from scratch. |

### Using the library

Include `libft.h` in your C program. For example, in a separate `main.c`:

```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    printf("Length: %zu\n", ft_strlen("1337"));
    return (0);
}
```

Build the library and then link your program against it:

```sh
make
cc -Wall -Wextra -Werror main.c -L. -lft -o program
./program
```

Expected output:

```text
Length: 4
```

The example `main.c` is illustrative and is not part of the submitted library sources.

## Testing

During development, the project was checked using Norminette, custom function tests, allocation-failure tests, and Valgrind. Local testing reported **53/53 regular test groups** and **62/62 groups with simulated allocation failures** passing, with no errors reported by Valgrind in the regular tests. These checks are not a guarantee that every possible input or official evaluation case will pass.

Test programs and generated executables are development tools and are not needed to compile the submitted library.

## Resources

### Documentation and references

- [C language reference — cppreference](https://en.cppreference.com/w/c/language)
- [C standard library reference — cppreference](https://en.cppreference.com/w/c/header)
- [Linux manual pages — man7.org](https://man7.org/linux/man-pages/)
- [GNU Make manual](https://www.gnu.org/software/make/manual/)
- [42 Norminette](https://github.com/42School/norminette)
- The official **Libft v19.3 subject** and **42 Norm v4.1** documents provided for the project.

### AI usage disclosure

AI assistance (ChatGPT) was used during development for:

- Explaining C concepts, including pointers, pointer-to-pointer arguments, memory overlap, dynamic allocation, callbacks, and linked-list traversal.
- Guiding and reviewing implementations, including linked-list functions and debugging issues such as character comparisons in `ft_strchr`.
- Assisting with some implementation code and corrections, especially during earlier parts of the project.
- Generating and improving local test programs, including edge-case and forced-allocation-failure checks.
- Helping draft this README and interpret build, Norminette, and Valgrind output.

AI-generated explanations, code suggestions, and test results were reviewed and checked through compilation, testing, and further study. Understanding and defending each implementation remains the student's responsibility.
