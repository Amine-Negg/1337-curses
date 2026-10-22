/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 00:17:48 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/21 20:50:52 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void	print_bytes(const void *memory, size_t n)
{
	const unsigned char	*p;
	size_t				i;

	p = (const unsigned char *) memory;
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

		char	dest1[20] =
		{
			0
		};
		char	dest2[20] =
		{
			0
		};
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
		printf("Start address: %p\n", (void *) str);
		printf("My result address: %p\n", (void *) result);
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
		printf("My result: %p\n", (void *) result);
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
		printf("My address: %p\n", (void *) result);
		printf("Original:   %p\n", (void *) strchr(str, 'l'));
		if (result != NULL)
		{
			printf("Character: %c\n", *result);
			printf("String from result: %s\n", result);
			printf("Index: %ld\n", (long)(result - str));
		}
		printf("\nSearch 'Z' (not found):\n");
		result = ft_strchr(str, 'Z');
		printf("My result: %p\n", (void *) result);
		printf("Original:  %p\n", (void *) strchr(str, 'Z'));
		printf("\nSearch '\\0':\n");
		result = ft_strchr(str, '\0');
		printf("My address: %p\n", (void *) result);
		printf("Original:   %p\n",
			(void *) strchr(str, '\0'));
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
		printf("My address: %p\n", (void *) result);
		printf("Original:   %p\n",
			(void *) strrchr(str, 'l'));
		if (result != NULL)
		{
			printf("Character: %c\n", *result);
			printf("String from result: %s\n", result);
			printf("Index: %ld\n", (long)(result - str));
		}
		printf("\nSearch 'Z' (not found):\n");
		result = ft_strrchr(str, 'Z');
		printf("My result: %p\n", (void *) result);
		printf("Original:  %p\n",
			(void *) strrchr(str, 'Z'));
		printf("\nSearch '\\0':\n");
		result = ft_strrchr(str, '\0');
		printf("My address: %p\n", (void *) result);
		printf("Original:   %p\n",
			(void *) strrchr(str, '\0'));
		if (result != NULL)
		{
			printf("Index: %ld\n", (long)(result - str));
			printf("Byte value: %d\n", (unsigned char)*result);
		}
	}
	printf("\n========== FT_STRNCMP ==========\n");
	printf("Test 1: %d\n", ft_strncmp("ABC", "ABC", 3));
	printf("Test 2: %d\n", ft_strncmp("ABC", "ABD", 3));
	printf("Test 3: %d\n", ft_strncmp("ABC", "ABCD", 4));
	printf("Test 4: %d\n", ft_strncmp("HELLO", "HELP", 3));
	printf("Test 5: %d\n", ft_strncmp("ABC", "XYZ", 0));
	printf("Test 6: %d\n", ft_strncmp("", "ABC", 3));
	printf("\n========== FT_ATOI ==========\n");
	printf("Test 1: ft=%d | original=%d\n",
		ft_atoi("42"), atoi("42"));
	printf("Test 2: ft=%d | original=%d\n",
		ft_atoi("--42"), atoi("--42"));
	printf("Test 3: ft=%d | original=%d\n",
		ft_atoi("   +123"), atoi("   +123"));
	printf("Test 4: ft=%d | original=%d\n",
		ft_atoi("123abc"), atoi("123abc"));
	printf("Test 5: ft=%d | original=%d\n",
		ft_atoi("abc123"), atoi("abc123"));
	printf("Test 6: ft=%d | original=%d\n",
		ft_atoi("--42"), atoi("--42"));
	printf("Test 7: ft=%d | original=%d\n",
		ft_atoi("+-42"), atoi("+-42"));
	printf("Test 8: ft=%d | original=%d\n",
		ft_atoi("\t\n -567"), atoi("\t\n -567"));
	printf("Test 8: ft=%d | original=%d\n",
		ft_atoi("     2147483647uv"), atoi("  2147483647"));
	printf("Test 8: ft=%d | original=%d\n",
		ft_atoi("     2147483648"), atoi("  2147483648"));
	printf("\n====================================\n");
	printf("         FT_STRLCPY TEST\n");
	printf("====================================\n");
	{
		char	src[] = "Hello World";
		char	dst[20] = "AAAAAAAAAAAAAAAAAAA";
		size_t	result;

		printf("\n--- TEST 1: Enough space ---\n");
		printf("Source before: %s\n", src);
		printf("Destination before: %s\n", dst);
		result = ft_strlcpy(dst, src, sizeof(dst));
		printf("Destination after: %s\n", dst);
		printf("Return value: %zu\n", result);
		printf("Expected: Hello World | Return: 11\n");
	}
	{
		char	src[] = "Hello World";
		char	dst[5] = "AAAA";
		size_t	result;

		printf("\n--- TEST 2: Small destination ---\n");
		printf("Source: %s\n", src);
		printf("Destination before: %s\n", dst);
		result = ft_strlcpy(dst, src, sizeof(dst));
		printf("Destination after: %s\n", dst);
		printf("Return value: %zu\n", result);
		printf("Expected: Hell | Return: 11\n");
	}
	{
		char	src[] = "Hello";
		char	dst[5] = "ABCD";
		size_t	result;

		printf("\n--- TEST 3: dstsize = 0 ---\n");
		printf("Destination before: %s\n", dst);
		result = ft_strlcpy(dst, src, 0);
		printf("Destination after: %s\n", dst);
		printf("Return value: %zu\n", result);
		printf("Expected: ABCD | Return: 5\n");
	}
	{
		char	src[] = "Hello";
		char	dst[5] = "ABCD";
		size_t	result;

		printf("\n--- TEST 4: dstsize = 1 ---\n");
		result = ft_strlcpy(dst, src, 1);
		printf("Destination after: \"%s\"\n", dst);
		printf("First byte value: %d\n", (unsigned char) dst[0]);
		printf("Return value: %zu\n", result);
		printf("Expected: \"\" | First byte: 0 | Return: 5\n");
	}
	{
		char	src[] = "";
		char	dst[10] = "AAAA";
		size_t	result;

		printf("\n--- TEST 5: Empty source ---\n");
		result = ft_strlcpy(dst, src, sizeof(dst));
		printf("Destination after: \"%s\"\n", dst);
		printf("Return value: %zu\n", result);
		printf("Expected: \"\" | Return: 0\n");
	}
	



	printf("\n========== FT_STRLCAT ==========\n");

	{
		char dst[12] = "Hello ";
		size_t result;

		result = ft_strlcat(dst, "World", sizeof(dst));
		printf("Test 1: %s | Return: %zu\n", dst, result);
	}

	{
		char dst[8] = "Hello";
		size_t result;

		result = ft_strlcat(dst, "World", sizeof(dst));
		printf("Test 2: %s | Return: %zu\n", dst, result);
	}

	{
		char dst[5] = "Hell";
		size_t result;

		result = ft_strlcat(dst, "World", 4);
		printf("Test 3: %s | Return: %zu\n", dst, result);
	}

	{
		char dst[5] = "ABC";
		size_t result;

		result = ft_strlcat(dst, "XYZ", 0);
		printf("Test 4: %s | Return: %zu\n", dst, result);
	}

	
	
	printf("\n========== FT_calloc ==========\n");
		



	printf("\n======================================\n");
	printf("          END OF LIBFT TESTS\n");
	printf("======================================\n");
	return (0);
}
