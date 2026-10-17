
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void	print_bytes(const void *memory, size_t n)
{
	const unsigned char	*p;
	size_t				i;

	p = (const unsigned char *)memory;
	i = 0;
	while (i < n)
	{
		printf("%02X ", p[i]);
		i++;
	}
	printf("\n");
}

int	main(void)
{
	char	*result;

	printf("\n======================================\n");
	printf("          MY LIBFT TESTER\n");
	printf("======================================\n");

	/* ===================================== */
	/* CHARACTER FUNCTIONS */
	/* ===================================== */

	printf("\n========== FT_ISALPHA ==========\n");
	printf("'A' -> ft: %d | original: %d\n", ft_isalpha('A'), isalpha('A'));
	printf("'z' -> ft: %d | original: %d\n", ft_isalpha('z'), isalpha('z'));
	printf("'8' -> ft: %d | original: %d\n", ft_isalpha('8'), isalpha('8'));

	printf("\n========== FT_ISDIGIT ==========\n");
	printf("'5' -> ft: %d | original: %d\n", ft_isdigit('5'), isdigit('5'));
	printf("'A' -> ft: %d | original: %d\n", ft_isdigit('A'), isdigit('A'));

	printf("\n========== FT_ISALNUM ==========\n");
	printf("'A' -> ft: %d | original: %d\n", ft_isalnum('A'), isalnum('A'));
	printf("'7' -> ft: %d | original: %d\n", ft_isalnum('7'), isalnum('7'));
	printf("'@' -> ft: %d | original: %d\n", ft_isalnum('@'), isalnum('@'));

	printf("\n========== FT_ISASCII ==========\n");
	printf("65  -> %d (expected nonzero)\n", ft_isascii(65));
	printf("127 -> %d (expected nonzero)\n", ft_isascii(127));
	printf("128 -> %d (expected 0)\n", ft_isascii(128));
	printf("-1  -> %d (expected 0)\n", ft_isascii(-1));

	printf("\n========== FT_ISPRINT ==========\n");
	printf("'A' -> ft: %d | original: %d\n", ft_isprint('A'), isprint('A'));
	printf("' ' -> ft: %d | original: %d\n", ft_isprint(' '), isprint(' '));
	printf("'\\n' -> ft: %d | original: %d\n", ft_isprint('\n'), isprint('\n'));

	printf("\n========== FT_TOUPPER ==========\n");
	printf("'a' -> ft: %c | original: %c\n", ft_toupper('a'), toupper('a'));
	printf("'z' -> ft: %c | original: %c\n", ft_toupper('z'), toupper('z'));
	printf("'5' -> ft: %c | original: %c\n", ft_toupper('5'), toupper('5'));

	printf("\n========== FT_TOLOWER ==========\n");
	printf("'A' -> ft: %c | original: %c\n", ft_tolower('A'), tolower('A'));
	printf("'Z' -> ft: %c | original: %c\n", ft_tolower('Z'), tolower('Z'));
	printf("'5' -> ft: %c | original: %c\n", ft_tolower('5'), tolower('5'));

	/* ===================================== */
	/* STRING LENGTH */
	/* ===================================== */

	printf("\n========== FT_STRLEN ==========\n");

	printf("\"Hello\" -> ft: %zu | original: %zu\n",
		ft_strlen("Hello"), strlen("Hello"));

	printf("\"\" -> ft: %zu | original: %zu\n",
		ft_strlen(""), strlen(""));

	printf("\"42 Network\" -> ft: %zu | original: %zu\n",
		ft_strlen("42 Network"), strlen("42 Network"));

	/* ===================================== */
	/* MEMORY FUNCTIONS */
	/* ===================================== */

	printf("\n========== FT_MEMSET ==========\n");
	{
		char	a[] = "Hello";
		char	b[] = "Hello";

		printf("Before ft_memset: %s\n", a);

		ft_memset(a, 'A', 3);
		memset(b, 'A', 3);

		printf("My ft_memset:      %s\n", a);
		printf("Original memset:   %s\n", b);

		printf("\nFill first 2 bytes with zero:\n");
		ft_memset(a, 0, 2);
		printf("Memory in HEX: ");
		print_bytes(a, sizeof(a));
	}

	printf("\n========== FT_BZERO ==========\n");
	{
		char	a[] = "ABCDEFG";
		char	b[] = "ABCDEFG";

		printf("Before: %s\n", a);

		ft_bzero(a, 3);
		memset(b, 0, 3);

		printf("My ft_bzero HEX:   ");
		print_bytes(a, sizeof(a));

		printf("Original zero HEX: ");
		print_bytes(b, sizeof(b));

		printf("Byte at index 3: %c\n", a[3]);
	}

	printf("\n========== FT_MEMCPY ==========\n");
	{
		char	src[] = "Hello World";
		char	dest1[20] = {0};
		char	dest2[20] = {0};

		printf("Source: %s\n", src);
		printf("Destination before: \"%s\"\n", dest1);

		ft_memcpy(dest1, src, 5);
		memcpy(dest2, src, 5);

		printf("My ft_memcpy:      \"%s\"\n", dest1);
		printf("Original memcpy:   \"%s\"\n", dest2);
		printf("Source afterward:  \"%s\"\n", src);

		printf("Destination HEX: ");
		print_bytes(dest1, 8);
	}

	printf("\n========== FT_MEMCHR ==========\n");
	{
		char	str[] = "amine neggaoui";

		printf("String: %s\n", str);
		printf("Searching for 'n' in first 15 bytes\n");

		result = ft_memchr(str, 'n', 15);

		printf("Start address: %p\n", (void *)str);
		printf("My result address: %p\n", (void *)result);
		printf("Original address:  %p\n",
			memchr(str, 'n', 15));

		if (result != NULL)
		{
			printf("Character found: %c\n", *result);
			printf("Remaining string: %s\n", result);
			printf("Index found: %ld\n", (long)(result - str));
		}

		printf("\nSearching for 'Z':\n");
		result = ft_memchr(str, 'Z', 15);
		printf("My result: %p\n", (void *)result);
		printf("Original:  %p\n", memchr(str, 'Z', 15));

		printf("\nSearching with n = 0:\n");
		printf("Result: %p\n", ft_memchr(str, 'a', 0));
	}

	printf("\n========== FT_MEMCMP ==========\n");
	{
		char	a[] = "TEST";
		char	b[] = "TESh";

		printf("String 1: %s\n", a);
		printf("String 2: %s\n", b);

		printf("My ft_memcmp:    %d\n", ft_memcmp(a, b, 5));
		printf("Original memcmp: %d\n", memcmp(a, b, 5));

		printf("\nEqual strings:\n");
		printf("My:       %d\n", ft_memcmp("ABC", "ABC", 3));
		printf("Original: %d\n", memcmp("ABC", "ABC", 3));

		printf("\nFirst smaller:\n");
		printf("My:       %d\n", ft_memcmp("ABC", "ABD", 3));
		printf("Original: %d\n", memcmp("ABC", "ABD", 3));

		printf("\nFirst greater:\n");
		printf("My:       %d\n", ft_memcmp("ABD", "ABC", 3));
		printf("Original: %d\n", memcmp("ABD", "ABC", 3));

		printf("\nZero bytes to compare:\n");
		printf("My:       %d\n", ft_memcmp("ABC", "XYZ", 0));
		printf("Original: %d\n", memcmp("ABC", "XYZ", 0));
	}

	/* ===================================== */
	/* STRING SEARCH FUNCTIONS */
	/* ===================================== */

	printf("\n========== FT_STRCHR ==========\n");
	{
		char	str[] = "Hello World";

		printf("String: %s\n", str);
		printf("Search first 'l':\n");

		result = ft_strchr(str, 'l');

		printf("My address: %p\n", (void *)result);
		printf("Original:   %p\n", (void *)strchr(str, 'l'));

		if (result != NULL)
		{
			printf("Character: %c\n", *result);
			printf("String from result: %s\n", result);
			printf("Index: %ld\n", (long)(result - str));
		}

		printf("\nSearch 'Z' (not found):\n");
		result = ft_strchr(str, 'Z');
		printf("My result: %p\n", (void *)result);
		printf("Original:  %p\n", (void *)strchr(str, 'Z'));

		printf("\nSearch '\\0':\n");
		result = ft_strchr(str, '\0');
		printf("My address: %p\n", (void *)result);
		printf("Original:   %p\n",
			(void *)strchr(str, '\0'));

		if (result != NULL)
		{
			printf("Index: %ld\n", (long)(result - str));
			printf("Byte value: %d\n", (unsigned char)*result);
		}
	}

	printf("\n========== FT_STRRCHR ==========\n");
	{
		char	str[] = "Hello World";

		printf("String: %s\n", str);
		printf("Search LAST 'l':\n");

		result = ft_strrchr(str, 'l');

		printf("My address: %p\n", (void *)result);
		printf("Original:   %p\n",
			(void *)strrchr(str, 'l'));

		if (result != NULL)
		{
			printf("Character: %c\n", *result);
			printf("String from result: %s\n", result);
			printf("Index: %ld\n", (long)(result - str));
		}

		printf("\nSearch 'Z' (not found):\n");
		result = ft_strrchr(str, 'Z');
		printf("My result: %p\n", (void *)result);
		printf("Original:  %p\n",
			(void *)strrchr(str, 'Z'));

		printf("\nSearch '\\0':\n");
		result = ft_strrchr(str, '\0');

		printf("My address: %p\n", (void *)result);
		printf("Original:   %p\n",
			(void *)strrchr(str, '\0'));

		if (result != NULL)
		{
			printf("Index: %ld\n", (long)(result - str));
			printf("Byte value: %d\n", (unsigned char)*result);
		}
	}

	printf("\n======================================\n");
	printf("          END OF LIBFT TESTS\n");
	printf("======================================\n");

	return (0);
}
