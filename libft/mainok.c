#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Automatic Libft tester. This file is NOT part of libft.a. */
/* Each test runs in a child process to contain crashes and infinite loops. */

static int equal_sign(int a, int b)
{
	return ((a > 0) == (b > 0) && (a < 0) == (b < 0));
}

static int equal_alloc(char *got, const char *want)
{
	int ok;

	ok = (got != NULL && strcmp(got, want) == 0);
	free(got);
	return (ok);
}

static char uppercase_even(unsigned int i, char c)
{
	if (i % 2 == 0 && c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	return (c);
}

static void uppercase_even_ptr(unsigned int i, char *c)
{
	if (i % 2 == 0 && *c >= 'a' && *c <= 'z')
		*c = *c - 'a' + 'A';
}

static int t_isalpha(void)
{
	return (!!ft_isalpha('A') == !!isalpha('A') &&
		!!ft_isalpha('z') == !!isalpha('z') &&
		ft_isalpha('8') == 0 && ft_isalpha(' ') == 0);
}

static int t_isdigit(void)
{
	return (!!ft_isdigit('0') == !!isdigit('0') &&
		!!ft_isdigit('9') == !!isdigit('9') &&
		ft_isdigit('a') == 0 && ft_isdigit('/') == 0);
}

static int t_isalnum(void)
{
	return (ft_isalnum('A') != 0 && ft_isalnum('6') != 0 &&
		ft_isalnum('@') == 0 && ft_isalnum(' ') == 0);
}

static int t_isascii(void)
{
	return (ft_isascii(0) != 0 && ft_isascii(127) != 0 &&
		ft_isascii(128) == 0 && ft_isascii(-1) == 0);
}

static int t_isprint(void)
{
	return (ft_isprint(32) != 0 && ft_isprint(126) != 0 &&
		ft_isprint(31) == 0 && ft_isprint(127) == 0);
}

static int t_strlen(void)
{
	return (ft_strlen("") == 0 && ft_strlen("1337") == 4 &&
		ft_strlen("Hello World") == 11);
}

static int t_memset(void)
{
	unsigned char a[12];
	unsigned char b[12];

	memset(a, 'q', sizeof(a));
	memset(b, 'q', sizeof(b));
	if (ft_memset(a + 1, 300, 6) != a + 1)
		return (0);
	memset(b + 1, 300, 6);
	return (memcmp(a, b, sizeof(a)) == 0);
}

static int t_bzero(void)
{
	unsigned char a[12];
	unsigned char b[12];

	memset(a, 0x7f, sizeof(a));
	memset(b, 0x7f, sizeof(b));
	ft_bzero(a + 2, 7);
	memset(b + 2, 0, 7);
	return (memcmp(a, b, sizeof(a)) == 0);
}

static int t_memcpy(void)
{
	char a[16] = "xxxxxxxxxxxxxxx";
	char b[16] = "xxxxxxxxxxxxxxx";
	const char src[] = "42\0Network";

	if (ft_memcpy(a, src, sizeof(src)) != a)
		return (0);
	memcpy(b, src, sizeof(src));
	return (memcmp(a, b, sizeof(a)) == 0);
}

static int t_memmove(void)
{
	char a[16] = "abcdefghi";
	char b[16] = "abcdefghi";

	if (ft_memmove(a + 2, a, 6) != a + 2)
		return (0);
	memmove(b + 2, b, 6);
	if (memcmp(a, b, sizeof(a)) != 0)
		return (0);
	if (ft_memmove(a, a + 2, 6) != a)
		return (0);
	memmove(b, b + 2, 6);
	return (memcmp(a, b, sizeof(a)) == 0);
}

static int t_strlcpy(void)
{
	char a[8] = "xxxxxxx";
	char b[8] = "xxxxxxx";

	if (ft_strlcpy(a, "HelloWorld", sizeof(a)) != 10 ||
		strcmp(a, "HelloWo") != 0)
		return (0);
	if (ft_strlcpy(b, "Hello", 0) != 5 || strcmp(b, "xxxxxxx") != 0)
		return (0);
	return (ft_strlcpy(a, "", sizeof(a)) == 0 && a[0] == '\0');
}

static int t_strlcat(void)
{
	char a[16] = "Hello";
	char b[5] = "abcd";
	char c[5] = "abcd";

	if (ft_strlcat(a, " World", sizeof(a)) != 11 ||
		strcmp(a, "Hello World") != 0)
		return (0);
	if (ft_strlcat(b, "XYZ", 3) != 6 || strcmp(b, c) != 0)
		return (0);
	return (ft_strlcat(a, "!", 0) == 1);
}

static int t_toupper(void)
{
	return (ft_toupper('a') == 'A' && ft_toupper('z') == 'Z' &&
		ft_toupper('!') == '!' && ft_toupper('A') == 'A');
}

static int t_tolower(void)
{
	return (ft_tolower('A') == 'a' && ft_tolower('Z') == 'z' &&
		ft_tolower('!') == '!' && ft_tolower('a') == 'a');
}

static int t_strchr(void)
{
	const char s[] = "banana";

	return (ft_strchr(s, 'a') == strchr(s, 'a') &&
		ft_strchr(s, '\0') == strchr(s, '\0') &&
		ft_strchr(s, 'x') == NULL);
}

static int t_strrchr(void)
{
	const char s[] = "banana";

	return (ft_strrchr(s, 'a') == strrchr(s, 'a') &&
		ft_strrchr(s, '\0') == strrchr(s, '\0') &&
		ft_strrchr(s, 'x') == NULL);
}

static int t_strncmp(void)
{
	return (ft_strncmp("abc", "abd", 2) == 0 &&
		equal_sign(ft_strncmp("abc", "abd", 3), strncmp("abc", "abd", 3)) &&
		equal_sign(ft_strncmp("abc", "ab", 4), strncmp("abc", "ab", 4)) &&
		ft_strncmp("abc", "xyz", 0) == 0);
}

static int t_memchr(void)
{
	const unsigned char bytes[] = {0x00, 0xff, 0x41, 0x00};

	return (ft_memchr(bytes, 0xff, 4) == memchr(bytes, 0xff, 4) &&
		ft_memchr(bytes, 0x141, 4) == memchr(bytes, 0x141, 4) &&
		ft_memchr(bytes, 0xff, 1) == NULL &&
		ft_memchr(bytes, 0, 0) == NULL);
}

static int t_memcmp(void)
{
	const unsigned char a[] = {0x00, 0xff, 0x42};
	const unsigned char b[] = {0x00, 0x7f, 0x42};

	return (equal_sign(ft_memcmp(a, b, 3), memcmp(a, b, 3)) &&
		equal_sign(ft_memcmp(b, a, 3), memcmp(b, a, 3)) &&
		ft_memcmp(a, a, 3) == 0 && ft_memcmp(a, b, 1) == 0 &&
		ft_memcmp(a, b, 0) == 0);
}

static int t_strnstr(void)
{
	const char s[] = "Hello World";

	return (ft_strnstr(s, "World", 11) == s + 6 &&
		ft_strnstr(s, "World", 10) == NULL &&
		ft_strnstr(s, "", 0) == s &&
		ft_strnstr(s, "xyz", 11) == NULL &&
		ft_strnstr(s, "Hello", 5) == s);
}

static int t_atoi(void)
{
	return (ft_atoi("42") == atoi("42") &&
		ft_atoi(" \t\n-123xyz") == atoi(" \t\n-123xyz") &&
		ft_atoi("+0") == 0 && ft_atoi("--42") == 0 &&
		ft_atoi("2147483647") == INT_MAX &&
		ft_atoi("-2147483648") == INT_MIN);
}

static int t_calloc(void)
{
	unsigned char *p;
	size_t i;

	p = ft_calloc(20, 2);
	if (!p)
		return (0);
	i = 0;
	while (i < 40)
	{
		if (p[i++] != 0)
		{
			free(p);
			return (0);
		}
	}
	free(p);
	p = ft_calloc(SIZE_MAX, 2);
	if (p)
		free(p);
	return (p == NULL);
}

static int t_strdup(void)
{
	char *p;

	p = ft_strdup("42 School");
	if (!p || strcmp(p, "42 School") != 0)
	{
		free(p);
		return (0);
	}
	free(p);
	return (equal_alloc(ft_strdup(""), ""));
}

static int t_substr(void)
{
	return (equal_alloc(ft_substr("Hello World", 6, 5), "World") &&
		equal_alloc(ft_substr("abc", 10, 4), "") &&
		equal_alloc(ft_substr("abc", 1, 99), "bc") &&
		equal_alloc(ft_substr("abc", 0, 0), ""));
}

static int t_strjoin(void)
{
	return (equal_alloc(ft_strjoin("Hello ", "1337"), "Hello 1337") &&
		equal_alloc(ft_strjoin("", "abc"), "abc") &&
		equal_alloc(ft_strjoin("abc", ""), "abc") &&
		equal_alloc(ft_strjoin("", ""), ""));
}

static int t_strtrim(void)
{
	return (equal_alloc(ft_strtrim("abcHELLOcba", "abc"), "HELLO") &&
		equal_alloc(ft_strtrim("aaaa", "a"), "") &&
		equal_alloc(ft_strtrim("  Hello 1337  ", " "), "Hello 1337") &&
		equal_alloc(ft_strtrim("", "a"), "") &&
		equal_alloc(ft_strtrim("abc", ""), "abc"));
}

static int split_matches(const char *s, char sep,
	const char *const *expected, size_t count)
{
	char **arr;
	size_t i;
	int ok;

	arr = ft_split(s, sep);
	if (!arr)
		return (0);
	i = 0;
	ok = 1;
	while (i < count && arr[i])
	{
		if (strcmp(arr[i], expected[i]) != 0)
			ok = 0;
		i++;
	}
	if (i != count || arr[i] != NULL)
		ok = 0;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (ok);
}

static int t_split(void)
{
	const char *a[] = {"42", "Network", "1337"};
	const char *b[] = {"Hello"};

	return (split_matches("42,,,Network,,1337", ',', a, 3) &&
		split_matches(",,Hello,,", ',', b, 1) &&
		split_matches(",,,", ',', NULL, 0) &&
		split_matches("", ',', NULL, 0) &&
		split_matches("Hello", ',', b, 1));
}

static int t_itoa(void)
{
	return (equal_alloc(ft_itoa(0), "0") &&
		equal_alloc(ft_itoa(42), "42") &&
		equal_alloc(ft_itoa(-1337), "-1337") &&
		equal_alloc(ft_itoa(INT_MAX), "2147483647") &&
		equal_alloc(ft_itoa(INT_MIN), "-2147483648"));
}

static int t_strmapi(void)
{
	const char *source = "abcdef";

	return (equal_alloc(ft_strmapi(source, uppercase_even), "AbCdEf") &&
		strcmp(source, "abcdef") == 0 &&
		equal_alloc(ft_strmapi("", uppercase_even), ""));
}

static int t_striteri(void)
{
	char str[] = "abcdef";
	char empty[] = "";

	ft_striteri(str, uppercase_even_ptr);
	ft_striteri(empty, uppercase_even_ptr);
	return (strcmp(str, "AbCdEf") == 0 && empty[0] == '\0');
}

static int fd_test(int which)
{
	int fds[2];
	char output[128];
	const char *expected;
	ssize_t n;

	if (pipe(fds) != 0)
		return (0);
	if (which == 0)
	{
		ft_putchar_fd('A', fds[1]);
		expected = "A";
	}
	else if (which == 1)
	{
		ft_putstr_fd("Hello 1337", fds[1]);
		expected = "Hello 1337";
	}
	else if (which == 2)
	{
		ft_putendl_fd("Hello", fds[1]);
		expected = "Hello\n";
	}
	else
	{
		ft_putnbr_fd(INT_MIN, fds[1]);
		expected = "-2147483648";
	}
	close(fds[1]);
	n = read(fds[0], output, sizeof(output) - 1);
	close(fds[0]);
	if (n < 0)
		return (0);
	output[n] = '\0';
	return (strcmp(output, expected) == 0);
}

static int t_putchar_fd(void) { return (fd_test(0)); }
static int t_putstr_fd(void) { return (fd_test(1)); }
static int t_putendl_fd(void) { return (fd_test(2)); }
static int t_putnbr_fd(void) { return (fd_test(3)); }

typedef int (*t_test_fn)(void);

typedef struct s_test
{
	const char *name;
	t_test_fn fn;
} t_test;

static int run_one(const t_test *test)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		alarm(3);
		_exit(test->fn() ? 0 : 1);
	}
	if (waitpid(pid, &status, 0) != pid)
		return (0);
	return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
}

int main(void)
{
	const t_test tests[] = {
		{"ft_isalpha", t_isalpha}, {"ft_isdigit", t_isdigit},
		{"ft_isalnum", t_isalnum}, {"ft_isascii", t_isascii},
		{"ft_isprint", t_isprint}, {"ft_strlen", t_strlen},
		{"ft_memset", t_memset}, {"ft_bzero", t_bzero},
		{"ft_memcpy", t_memcpy}, {"ft_memmove", t_memmove},
		{"ft_strlcpy", t_strlcpy}, {"ft_strlcat", t_strlcat},
		{"ft_toupper", t_toupper}, {"ft_tolower", t_tolower},
		{"ft_strchr", t_strchr}, {"ft_strrchr", t_strrchr},
		{"ft_strncmp", t_strncmp}, {"ft_memchr", t_memchr},
		{"ft_memcmp", t_memcmp}, {"ft_strnstr", t_strnstr},
		{"ft_atoi", t_atoi}, {"ft_calloc", t_calloc},
		{"ft_strdup", t_strdup}, {"ft_substr", t_substr},
		{"ft_strjoin", t_strjoin}, {"ft_strtrim", t_strtrim},
		{"ft_split", t_split}, {"ft_itoa", t_itoa},
		{"ft_strmapi", t_strmapi}, {"ft_striteri", t_striteri},
		{"ft_putchar_fd", t_putchar_fd},
		{"ft_putstr_fd", t_putstr_fd},
		{"ft_putendl_fd", t_putendl_fd},
		{"ft_putnbr_fd", t_putnbr_fd}
	};
	size_t i;
	int passed;
	int ok;

	passed = 0;
	i = 0;
	while (i < sizeof(tests) / sizeof(tests[0]))
	{
		ok = run_one(&tests[i]);
		printf("%-18s : %s\n", tests[i].name, ok ? "OK" : "KO");
		passed += ok;
		i++;
	}
	printf("\n%d/%zu functions OK\n", passed,
		sizeof(tests) / sizeof(tests[0]));
	if (passed == (int)(sizeof(tests) / sizeof(tests[0])))
	{
		printf("\nALL TESTS: OK\n");
		return (0);
	}
	printf("\nALL TESTS: KO (see failed functions)\n");
	return (1);
}
