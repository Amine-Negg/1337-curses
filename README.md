*This project has been created as part of the 42 curriculum by <mkassbi>.*

# Libft

## Description

Libft is a custom C library developed as part of the 42 School curriculum.

The main goal of this project is to recreate several standard C library
functions from scratch in order to understand how they work internally.

This project helps develop a better understanding of:
- Memory management and dynamic allocation.
- Pointers and pointer manipulation.
- String manipulation.
- Data structures, especially linked lists.
- Working with file descriptors.
- Writing reusable and well-structured C code.

The library is compiled into a static library named `libft.a`, which
can be reused in future C projects.

## Instructions

Library Description
Libft contains several groups of functions that reproduce or extend
the behavior of standard C library functions.
1. Character Checking and Conversion
These functions check character types and convert between uppercase
and lowercase letters.
- ft_isalpha
- ft_isdigit
- ft_isalnum
- ft_isascii
- ft_isprint
- ft_toupper
- ft_tolower
2. String Functions
These functions calculate string lengths, search for characters,
compare strings, and manipulate string content.
- ft_strlen
- ft_strchr
- ft_strrchr
- ft_strncmp
- ft_strlcpy
- ft_strlcat
- ft_strnstr
- ft_strdup
- ft_substr
- ft_strjoin
- ft_strtrim
- ft_split
- ft_itoa
- ft_strmapi
- ft_striteri
3. Memory Functions
These functions manipulate memory areas and handle dynamic memory
allocation.
- ft_memset
- ft_bzero
- ft_memcpy
- ft_memmove
- ft_memchr
- ft_memcmp
- ft_calloc
4. Conversion Functions
- ft_atoi
5. File Descriptor Functions
These functions write characters, strings, and numbers to a given
file descriptor.
- ft_putchar_fd
- ft_putstr_fd
- ft_putendl_fd
- ft_putnbr_fd
6. Linked List Functions
These functions manage singly linked lists using the t_list structure.

They allow creating nodes, adding and removing elements, accessing
list information, and applying operations to list contents.
- ft_lstnew
- ft_lstadd_front
- ft_lstadd_back
- ft_lstsize
- ft_lstlast
- ft_lstdelone
- ft_lstclear
- ft_lstiter
- ft_lstmap

### Compilation

To compile the library, run:

```bash
make
