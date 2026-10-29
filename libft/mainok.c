/*
 * 1337 / 42 LIBFT v19.3 -- HARD TESTER (43 functions)
 * This file is a TEST PROGRAM, not part of libft.a or your submission.
 * Linux / POSIX required (fork, waitpid, alarm, pipe).
 *
 * Build:
 *   make re
 *   cc -Wall -Wextra -Werror -O0 -g mainok.c -L. -lft -o mainok
 *   ./mainok
 *
 * Optional allocation-failure tests (GNU ld / Linux):
 *   cc -Wall -Wextra -Werror -O0 -g -DTEST_MALLOC_FAILURE \
 *       mainok.c -L. -lft -Wl,--wrap=malloc -o mainok_fail
 *   ./mainok_fail
 *
 * Optional valgrind (if installed):
 *   valgrind --leak-check=full --show-leak-kinds=all ./mainok
 *
 * Test limitations: no finite suite proves all inputs or all memory safety.
 * Deliberately avoids undefined-behavior inputs to standard C functions.
 */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <locale.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHECK(expr) do { if (!(expr)) { \
    fprintf(stderr, "    FAILED at line %d: %s\n", __LINE__, #expr); \
    return (0); \
} } while (0)

#define CASE(name, label, fn) { name, label, fn }

static unsigned int g_random = 0x13374242u;
static int g_del_calls;
static int g_iter_calls;
static int g_map_calls;

static unsigned int next_random(void)
{
    g_random ^= g_random << 13;
    g_random ^= g_random >> 17;
    g_random ^= g_random << 5;
    return (g_random);
}

static int same_sign(int x, int y)
{
    return ((x == 0 && y == 0) || (x < 0 && y < 0) || (x > 0 && y > 0));
}

static int same_owned_string(char *got, const char *want)
{
    int ok;

    ok = (got && strcmp(got, want) == 0);
    free(got);
    return (ok);
}

static size_t ref_strlcpy(char *dst, const char *src, size_t size)
{
    size_t i;
    size_t n;

    n = strlen(src);
    i = 0;
    if (size)
    {
        while (i + 1 < size && src[i])
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    return (n);
}

static size_t ref_strlcat(char *dst, const char *src, size_t size)
{
    size_t n;
    size_t slen;
    size_t i;

    n = 0;
    slen = strlen(src);
    while (n < size && dst[n])
        n++;
    if (n == size)
        return (size + slen);
    i = 0;
    while (n + i + 1 < size && src[i])
    {
        dst[n + i] = src[i];
        i++;
    }
    dst[n + i] = '\0';
    return (n + slen);
}

static char *ref_strnstr(const char *big, const char *little, size_t len)
{
    size_t i;
    size_t j;

    if (!little[0])
        return ((char *)big);
    i = 0;
    while (i < len && big[i])
    {
        j = 0;
        while (i + j < len && big[i + j] && little[j]
            && big[i + j] == little[j])
            j++;
        if (!little[j])
            return ((char *)big + i);
        i++;
    }
    return (NULL);
}

static char *ref_trim(const char *str, const char *set)
{
    size_t start;
    size_t end;
    char *result;

    start = 0;
    end = strlen(str);
    while (start < end && strchr(set, str[start]))
        start++;
    while (end > start && strchr(set, str[end - 1]))
        end--;
    result = malloc(end - start + 1);
    if (!result)
        return (NULL);
    memcpy(result, str + start, end - start);
    result[end - start] = '\0';
    return (result);
}

static char change_even(unsigned int i, char c)
{
    if (!(i % 2) && c >= 'a' && c <= 'z')
        return ((char)(c - 32));
    return (c);
}

static void change_even_ptr(unsigned int i, char *c)
{
    if (!(i % 2) && *c >= 'a' && *c <= 'z')
        *c = (char)(*c - 32);
}

/* ---------------- 23 libc equivalents ---------------- */

static int test_isalpha_all(void)
{
    int i;
    int expected;

    i = -1;
    while (i <= 255)
    {
        expected = (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z');
        CHECK(ft_isalpha(i) == expected);
        i++;
    }
    CHECK(ft_isalpha(256) == 0);
    CHECK(ft_isalpha(-42) == 0);
    return (1);
}

static int test_isdigit_all(void)
{
    int i;

    i = -1;
    while (i <= 255)
    {
        CHECK(ft_isdigit(i) == (i >= '0' && i <= '9'));
        i++;
    }
    CHECK(ft_isdigit(256) == 0);
    return (1);
}

static int test_isalnum_all(void)
{
    int i;
    int expected;

    i = -1;
    while (i <= 255)
    {
        expected = (i >= '0' && i <= '9') ||
            (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z');
        CHECK(ft_isalnum(i) == expected);
        i++;
    }
    CHECK(ft_isalnum(256) == 0);
    return (1);
}

static int test_isascii_all(void)
{
    int i;

    i = -100;
    while (i <= 300)
    {
        CHECK(ft_isascii(i) == (i >= 0 && i <= 127));
        i++;
    }
    CHECK(ft_isascii(INT_MIN) == 0);
    CHECK(ft_isascii(INT_MAX) == 0);
    return (1);
}

static int test_isprint_all(void)
{
    int i;

    i = -1;
    while (i <= 255)
    {
        CHECK(ft_isprint(i) == (i >= 32 && i <= 126));
        i++;
    }
    CHECK(ft_isprint(256) == 0);
    return (1);
}

static int test_strlen_limits(void)
{
    char buffer[4097];
    size_t i;

    CHECK(ft_strlen("") == 0);
    CHECK(ft_strlen("42\0hidden") == 2);
    CHECK(ft_strlen("a") == 1);
    memset(buffer, 'Q', sizeof(buffer));
    i = 0;
    while (i < 4096)
    {
        buffer[i] = '\0';
        CHECK(ft_strlen(buffer) == i);
        buffer[i] = 'Q';
        i++;
    }
    buffer[4096] = '\0';
    CHECK(ft_strlen(buffer) == 4096);
    return (1);
}

static int test_memset_sweep(void)
{
    unsigned char a[160];
    unsigned char b[160];
    int vals[] = {0, 1, 255, 256, -1, 0x1234};
    size_t n;
    size_t k;
    size_t off;

    k = 0;
    while (k < sizeof(vals) / sizeof(vals[0]))
    {
        off = 0;
        while (off <= 16)
        {
            n = 0;
            while (n <= 128)
            {
                memset(a, 0xA5, sizeof(a));
                memset(b, 0xA5, sizeof(b));
                CHECK(ft_memset(a + off, vals[k], n) == a + off);
                memset(b + off, vals[k], n);
                CHECK(!memcmp(a, b, sizeof(a)));
                n++;
            }
            off++;
        }
        k++;
    }
    return (1);
}

static int test_bzero_sweep(void)
{
    unsigned char a[160];
    unsigned char b[160];
    size_t n;
    size_t off;

    off = 0;
    while (off <= 16)
    {
        n = 0;
        while (n <= 128)
        {
            memset(a, 0x7F, sizeof(a));
            memset(b, 0x7F, sizeof(b));
            ft_bzero(a + off, n);
            memset(b + off, 0, n);
            CHECK(!memcmp(a, b, sizeof(a)));
            n++;
        }
        off++;
    }
    return (1);
}

static int test_memcpy_sweep(void)
{
    unsigned char a[192];
    unsigned char b[192];
    unsigned char src[160];
    size_t n;
    size_t off;
    size_t i;

    i = 0;
    while (i < sizeof(src))
    {
        src[i] = (unsigned char)next_random();
        i++;
    }
    off = 0;
    while (off <= 16)
    {
        n = 0;
        while (n <= 128)
        {
            memset(a, 0xBA, sizeof(a));
            memset(b, 0xBA, sizeof(b));
            CHECK(ft_memcpy(a + off, src, n) == a + off);
            memcpy(b + off, src, n);
            CHECK(!memcmp(a, b, sizeof(a)));
            n++;
        }
        off++;
    }
    return (1);
}

static int test_memmove_overlap(void)
{
    unsigned char a[160];
    unsigned char b[160];
    size_t src;
    size_t dst;
    size_t n;
    size_t i;

    src = 0;
    while (src <= 32)
    {
        dst = 0;
        while (dst <= 32)
        {
            n = 0;
            while (n <= 96)
            {
                i = 0;
                while (i < sizeof(a))
                {
                    a[i] = (unsigned char)(i * 37 + 11);
                    b[i] = a[i];
                    i++;
                }
                CHECK(ft_memmove(a + dst, a + src, n) == a + dst);
                memmove(b + dst, b + src, n);
                CHECK(!memcmp(a, b, sizeof(a)));
                n++;
            }
            dst++;
        }
        src++;
    }
    return (1);
}

static int test_strlcpy_boundaries(void)
{
    char a[100];
    char b[100];
    char src[64];
    size_t length;
    size_t size;

    length = 0;
    while (length <= 55)
    {
        memset(src, 'X', length);
        src[length] = '\0';
        size = 0;
        while (size <= 80)
        {
            memset(a, 0x6B, sizeof(a));
            memset(b, 0x6B, sizeof(b));
            CHECK(ft_strlcpy(a + 5, src, size) ==
                ref_strlcpy(b + 5, src, size));
            CHECK(!memcmp(a, b, sizeof(a)));
            size++;
        }
        length++;
    }
    return (1);
}

static int test_strlcat_boundaries(void)
{
    char a[112];
    char b[112];
    char src[48];
    size_t prefix;
    size_t suffix;
    size_t size;

    prefix = 0;
    while (prefix <= 28)
    {
        suffix = 0;
        while (suffix <= 28)
        {
            memset(src, 'S', suffix);
            src[suffix] = '\0';
            size = 0;
            while (size <= 65)
            {
                memset(a, 0x49, sizeof(a));
                memset(a + 4, 'D', prefix);
                a[4 + prefix] = '\0';
                memcpy(b, a, sizeof(a));
                CHECK(ft_strlcat(a + 4, src, size) ==
                    ref_strlcat(b + 4, src, size));
                CHECK(!memcmp(a, b, sizeof(a)));
                size++;
            }
            suffix++;
        }
        prefix++;
    }
    return (1);
}

static int test_toupper_all(void)
{
    int i;

    i = 0;
    while (i <= 255)
    {
        CHECK(ft_toupper(i) == toupper(i));
        i++;
    }
    CHECK(ft_toupper(EOF) == toupper(EOF));
    return (1);
}

static int test_tolower_all(void)
{
    int i;

    i = 0;
    while (i <= 255)
    {
        CHECK(ft_tolower(i) == tolower(i));
        i++;
    }
    CHECK(ft_tolower(EOF) == tolower(EOF));
    return (1);
}

static int test_strchr_all(void)
{
    char s[] = {'A', (char)0xFF, 'z', 'A', (char)0x80, '\0'};
    const char *cases[] = {"", "a", "banana", "aaaa", "123\0abc"};
    size_t j;
    int i;

    j = 0;
    while (j < sizeof(cases) / sizeof(cases[0]))
    {
        i = 0;
        while (i <= 255)
        {
            CHECK(ft_strchr(cases[j], i) == strchr(cases[j], i));
            i++;
        }
        j++;
    }
    i = 0;
    while (i <= 255)
    {
        CHECK(ft_strchr(s, i) == strchr(s, i));
        i++;
    }
    return (1);
}

static int test_strrchr_all(void)
{
    char s[] = {'A', (char)0xFF, 'z', 'A', (char)0x80, '\0'};
    const char *cases[] = {"", "a", "banana", "aaaa", "123\0abc"};
    size_t j;
    int i;

    j = 0;
    while (j < sizeof(cases) / sizeof(cases[0]))
    {
        i = 0;
        while (i <= 255)
        {
            CHECK(ft_strrchr(cases[j], i) == strrchr(cases[j], i));
            i++;
        }
        j++;
    }
    i = 0;
    while (i <= 255)
    {
        CHECK(ft_strrchr(s, i) == strrchr(s, i));
        i++;
    }
    return (1);
}

static int test_strncmp_sweep(void)
{
    char a[80];
    char b[80];
    size_t i;
    size_t n;
    size_t round;

    round = 0;
    while (round < 2000)
    {
        i = 0;
        while (i < sizeof(a) - 1)
        {
            a[i] = (char)(1 + next_random() % 255);
            b[i] = (char)(1 + next_random() % 255);
            i++;
        }
        a[round % 79] = '\0';
        b[(round * 7) % 79] = '\0';
        a[79] = '\0';
        b[79] = '\0';
        n = 0;
        while (n <= 80)
        {
            CHECK(same_sign(ft_strncmp(a, b, n), strncmp(a, b, n)));
            n++;
        }
        round++;
    }
    CHECK(ft_strncmp("a", "z", 0) == 0);
    return (1);
}

static int test_memchr_sweep(void)
{
    unsigned char data[128];
    size_t i;
    size_t n;
    int ch;

    i = 0;
    while (i < sizeof(data))
    {
        data[i] = (unsigned char)next_random();
        i++;
    }
    n = 0;
    while (n <= sizeof(data))
    {
        ch = -1;
        while (ch <= 256)
        {
            CHECK(ft_memchr(data, ch, n) == memchr(data, ch, n));
            ch++;
        }
        n++;
    }
    return (1);
}

static int test_memcmp_sweep(void)
{
    unsigned char a[129];
    unsigned char b[129];
    size_t i;
    size_t n;
    size_t round;

    round = 0;
    while (round < 2000)
    {
        i = 0;
        while (i < sizeof(a))
        {
            a[i] = (unsigned char)next_random();
            b[i] = (unsigned char)next_random();
            i++;
        }
        if (round % 3 == 0)
            memcpy(b, a, sizeof(a));
        if (round % 3 == 1)
            b[round % sizeof(b)] = a[round % sizeof(a)];
        n = 0;
        while (n <= sizeof(a))
        {
            CHECK(same_sign(ft_memcmp(a, b, n), memcmp(a, b, n)));
            n++;
        }
        round++;
    }
    CHECK(same_sign(ft_memcmp("\x80", "\x7f", 1),
        memcmp("\x80", "\x7f", 1)));
    return (1);
}

static int test_strnstr_boundaries(void)
{
    const char *big = "aaaaabcaaabcaabc";
    const char *little[] = {"", "a", "aaa", "abc", "aabc", "bc", "z"};
    size_t i;
    size_t n;

    i = 0;
    while (i < sizeof(little) / sizeof(little[0]))
    {
        n = 0;
        while (n <= strlen(big) + 2)
        {
            CHECK(ft_strnstr(big, little[i], n) ==
                ref_strnstr(big, little[i], n));
            n++;
        }
        i++;
    }
    CHECK(ft_strnstr("", "", 0) != NULL);
    CHECK(ft_strnstr("", "x", 0) == NULL);
    return (1);
}

static int test_strnstr_random(void)
{
    char big[60];
    char little[22];
    size_t i;
    size_t round;
    size_t n;

    round = 0;
    while (round < 3000)
    {
        i = 0;
        while (i < 59)
        {
            big[i] = (char)('a' + next_random() % 4);
            i++;
        }
        big[59] = 0;
        i = 0;
        while (i < 21)
        {
            little[i] = (char)('a' + next_random() % 4);
            i++;
        }
        little[round % 22] = 0;
        n = round % 60;
        CHECK(ft_strnstr(big, little, n) == ref_strnstr(big, little, n));
        round++;
    }
    return (1);
}

static int test_atoi_boundaries(void)
{
    const char *examples[] = {"", " ", "\t\n\v\f\r+42junk", "--42", "++42",
        "+-12", "-+12", "+0", "-0", "00042", "42abc", "  -2147483648",
        "2147483647", "-000001", "\t +00088x", " 12 34", "+", "-"};
    size_t i;

    i = 0;
    while (i < sizeof(examples) / sizeof(examples[0]))
    {
        CHECK(ft_atoi(examples[i]) == atoi(examples[i]));
        i++;
    }
    return (1);
}

static int test_atoi_random(void)
{
    char buffer[80];
    int value;
    int i;

    i = 0;
    while (i < 3000)
    {
        value = (int)(next_random() % 2000000001u) - 1000000000;
        snprintf(buffer, sizeof(buffer), " \t%+dEND", value);
        CHECK(ft_atoi(buffer) == atoi(buffer));
        i++;
    }
    return (1);
}

static int test_calloc_zeroing(void)
{
    size_t i;
    size_t size;
    unsigned char *p;
    size_t n;

    n = 1;
    while (n <= 64)
    {
        size = 1;
        while (size <= 64)
        {
            p = ft_calloc(n, size);
            CHECK(p != NULL);
            i = 0;
            while (i < n * size)
            {
                if (p[i] != 0)
                {
                    free(p);
                    CHECK(0);
                }
                i++;
            }
            free(p);
            size++;
        }
        n++;
    }
    return (1);
}

static int test_calloc_zero_and_overflow(void)
{
    unsigned char *a;
    unsigned char *b;
    volatile size_t huge;

    a = ft_calloc(0, 100);
    CHECK(a != NULL);
    b = ft_calloc(100, 0);
    CHECK(b != NULL);
    CHECK(a != b);
    free(a);
    free(b);
    huge = SIZE_MAX;
    a = ft_calloc(huge, 2);
    CHECK(a == NULL);
    a = ft_calloc(2, huge);
    CHECK(a == NULL);
    return (1);
}

static int test_strdup_cases(void)
{
    char original[5000];
    char *copy;
    size_t i;

    CHECK(same_owned_string(ft_strdup(""), ""));
    CHECK(same_owned_string(ft_strdup("1337\0hidden"), "1337"));
    i = 0;
    while (i < sizeof(original) - 1)
    {
        original[i] = (char)('a' + i % 26);
        i++;
    }
    original[i] = 0;
    copy = ft_strdup(original);
    CHECK(copy != NULL);
    CHECK(copy != original);
    CHECK(!strcmp(copy, original));
    original[0] = '#';
    CHECK(copy[0] != original[0]);
    free(copy);
    return (1);
}

/* ---------------- 11 additional functions ---------------- */

static int test_substr_edges(void)
{
    CHECK(same_owned_string(ft_substr("", 0, 0), ""));
    CHECK(same_owned_string(ft_substr("abc", 0, 0), ""));
    CHECK(same_owned_string(ft_substr("abc", 1, 0), ""));
    CHECK(same_owned_string(ft_substr("abc", 1, 2), "bc"));
    CHECK(same_owned_string(ft_substr("abc", 1, 100), "bc"));
    CHECK(same_owned_string(ft_substr("abc", 3, 4), ""));
    CHECK(same_owned_string(ft_substr("abc", 100, 4), ""));
    CHECK(same_owned_string(ft_substr("abc", UINT_MAX, 4), ""));
    return (1);
}

static int test_substr_random(void)
{
    char source[110];
    char expected[110];
    char *got;
    unsigned int start;
    size_t len;
    size_t available;
    size_t i;

    i = 0;
    while (i < 100)
    {
        source[i] = (char)('a' + (i * 7) % 26);
        i++;
    }
    source[100] = 0;
    i = 0;
    while (i < 3000)
    {
        start = next_random() % 130;
        len = next_random() % 130;
        available = start >= 100 ? 0 : 100 - start;
        if (available > len)
            available = len;
        if (available)
            memcpy(expected, source + start, available);
        expected[available] = '\0';
        got = ft_substr(source, start, len);
        CHECK(got != NULL);
        CHECK(!strcmp(got, expected));
        free(got);
        i++;
    }
    return (1);
}

static int test_strjoin_edges(void)
{
    char left[128];
    char right[128];
    char expected[256];
    char *got;
    size_t i;

    CHECK(same_owned_string(ft_strjoin("", ""), ""));
    CHECK(same_owned_string(ft_strjoin("a", ""), "a"));
    CHECK(same_owned_string(ft_strjoin("", "b"), "b"));
    CHECK(same_owned_string(ft_strjoin("42", "1337"), "421337"));
    i = 0;
    while (i < 128)
    {
        memset(left, 'A', i);
        left[i] = 0;
        memset(right, 'B', 127 - i);
        right[127 - i] = 0;
        snprintf(expected, sizeof(expected), "%s%s", left, right);
        got = ft_strjoin(left, right);
        CHECK(got != NULL);
        CHECK(!strcmp(got, expected));
        free(got);
        i++;
    }
    return (1);
}

static int test_strtrim_edges(void)
{
    CHECK(same_owned_string(ft_strtrim("", ""), ""));
    CHECK(same_owned_string(ft_strtrim("abc", ""), "abc"));
    CHECK(same_owned_string(ft_strtrim("ab", "ab"), ""));
    CHECK(same_owned_string(ft_strtrim("xxHELOxx", "x"), "HELO"));
    CHECK(same_owned_string(ft_strtrim("  Hello 42  ", " "), "Hello 42"));
    CHECK(same_owned_string(ft_strtrim("aaabbbccc", "abc"), ""));
    CHECK(same_owned_string(ft_strtrim("aaaXYZbbb", "ab"), "XYZ"));
    CHECK(same_owned_string(ft_strtrim("!!?hello!?!", "!?"), "hello"));
    return (1);
}

static int test_strtrim_random(void)
{
    char s[256];
    char *expected;
    char *got;
    size_t i;
    size_t round;

    round = 0;
    while (round < 2000)
    {
        i = 0;
        while (i < 255)
        {
            s[i] = (char)('a' + next_random() % 5);
            i++;
        }
        s[round % 256] = 0;
        expected = ref_trim(s, "abc");
        CHECK(expected != NULL);
        got = ft_strtrim(s, "abc");
        CHECK(got != NULL);
        CHECK(!strcmp(got, expected));
        free(got);
        free(expected);
        round++;
    }
    return (1);
}

static int split_check(const char *source, char sep, const char **expected,
    size_t expected_count)
{
    char **result;
    size_t i;
    int ok;

    result = ft_split(source, sep);
    CHECK(result != NULL);
    i = 0;
    ok = 1;
    while (i < expected_count && result[i])
    {
        if (strcmp(result[i], expected[i]) != 0)
            ok = 0;
        i++;
    }
    if (i != expected_count || result[i] != NULL)
        ok = 0;
    i = 0;
    while (result[i] && i < 10000)
    {
        free(result[i]);
        i++;
    }
    free(result);
    CHECK(ok);
    return (1);
}

static int test_split_edges(void)
{
    const char *a[] = {"a", "b", "c"};
    const char *b[] = {"hello"};
    const char *c[] = {"a", "b", "c"};
    const char *d[] = {"abc"};

    CHECK(split_check("", ',', NULL, 0));
    CHECK(split_check(",,,,,", ',', NULL, 0));
    CHECK(split_check("a,b,c", ',', a, 3));
    CHECK(split_check(",a,,b,c,", ',', a, 3));
    CHECK(split_check("hello", ',', b, 1));
    CHECK(split_check("a  b c", ' ', c, 3));
    CHECK(split_check("abc", '\0', d, 1));
    CHECK(split_check("", '\0', NULL, 0));
    return (1);
}

static int test_split_long_tokens(void)
{
    char source[5000];
    const char *expected[3];
    char first[2049];
    char second[1501];
    size_t i;

    memset(first, 'a', 2048);
    first[2048] = 0;
    memset(second, 'b', 1500);
    second[1500] = 0;
    i = 0;
    memcpy(source + i, first, 2048);
    i += 2048;
    source[i++] = '#';
    source[i++] = '#';
    memcpy(source + i, second, 1500);
    i += 1500;
    source[i++] = '#';
    memcpy(source + i, "last", 4);
    i += 4;
    source[i] = 0;
    expected[0] = first;
    expected[1] = second;
    expected[2] = "last";
    CHECK(split_check(source, '#', expected, 3));
    return (1);
}

static int test_split_many(void)
{
    char src[2600];
    const char *words[500];
    size_t n;
    size_t i;

    n = 0;
    i = 0;
    while (i < 250)
    {
        src[n++] = ',';
        src[n++] = 'x';
        src[n++] = ',';
        words[i] = "x";
        i++;
    }
    src[n] = 0;
    CHECK(split_check(src, ',', words, 250));
    return (1);
}

static int test_itoa_limits(void)
{
    const int cases[] = {0, 1, -1, 10, -10, 42, -42, INT_MIN, INT_MAX,
        1000000000, -1000000000, 100000, -100000};
    char expected[64];
    size_t i;

    i = 0;
    while (i < sizeof(cases) / sizeof(cases[0]))
    {
        snprintf(expected, sizeof(expected), "%d", cases[i]);
        CHECK(same_owned_string(ft_itoa(cases[i]), expected));
        i++;
    }
    return (1);
}

static int test_itoa_random(void)
{
    char expected[64];
    int value;
    int i;

    i = 0;
    while (i < 10000)
    {
        value = (int)next_random();
        snprintf(expected, sizeof(expected), "%d", value);
        CHECK(same_owned_string(ft_itoa(value), expected));
        i++;
    }
    return (1);
}

static int test_strmapi_cases(void)
{
    char original[512];
    char expected[512];
    char *got;
    size_t i;

    CHECK(same_owned_string(ft_strmapi("", change_even), ""));
    CHECK(same_owned_string(ft_strmapi("abcdef", change_even), "AbCdEf"));
    i = 0;
    while (i < 511)
    {
        original[i] = (char)('a' + i % 26);
        expected[i] = change_even((unsigned int)i, original[i]);
        i++;
    }
    original[i] = 0;
    expected[i] = 0;
    got = ft_strmapi(original, change_even);
    CHECK(got != NULL && got != original);
    CHECK(!strcmp(got, expected));
    CHECK(original[0] == 'a');
    free(got);
    return (1);
}

static int test_striteri_cases(void)
{
    char original[512];
    char expected[512];
    size_t i;

    i = 0;
    while (i < 511)
    {
        original[i] = (char)('a' + i % 26);
        expected[i] = change_even((unsigned int)i, original[i]);
        i++;
    }
    original[i] = 0;
    expected[i] = 0;
    ft_striteri(original, change_even_ptr);
    CHECK(!strcmp(original, expected));
    ft_striteri(original + 511, change_even_ptr);
    CHECK(original[511] == 0);
    return (1);
}

static int fd_compare(int which, const char *input, int number,
    const char *expected)
{
    int fds[2];
    char output[20000];
    ssize_t count;
    size_t total;

    CHECK(pipe(fds) == 0);
    if (which == 0)
        ft_putchar_fd(input[0], fds[1]);
    else if (which == 1)
        ft_putstr_fd((char *)input, fds[1]);
    else if (which == 2)
        ft_putendl_fd((char *)input, fds[1]);
    else
        ft_putnbr_fd(number, fds[1]);
    close(fds[1]);
    total = 0;
    count = read(fds[0], output, sizeof(output) - 1);
    while (count > 0)
    {
        total += (size_t)count;
        count = read(fds[0], output + total, sizeof(output) - 1 - total);
    }
    close(fds[0]);
    CHECK(count == 0);
    output[total] = 0;
    CHECK(strcmp(output, expected) == 0);
    return (1);
}

static int test_putchar_fd_binary(void)
{
    int fds[2];
    unsigned char got;
    int value;

    value = 0;
    while (value <= 255)
    {
        CHECK(pipe(fds) == 0);
        ft_putchar_fd((char)value, fds[1]);
        close(fds[1]);
        CHECK(read(fds[0], &got, 1) == 1);
        close(fds[0]);
        CHECK(got == (unsigned char)value);
        value++;
    }
    return (1);
}

static int test_putchar_fd_cases(void)
{
    char expected[2];
    char src[2];
    int i;

    i = 1;
    while (i <= 127)
    {
        src[0] = (char)i;
        src[1] = 0;
        expected[0] = (char)i;
        expected[1] = 0;
        CHECK(fd_compare(0, src, 0, expected));
        i++;
    }
    return (1);
}

static int test_putstr_fd_cases(void)
{
    char longstr[4097];

    CHECK(fd_compare(1, "", 0, ""));
    CHECK(fd_compare(1, "hello", 0, "hello"));
    CHECK(fd_compare(1, "1337\0hidden", 0, "1337"));
    memset(longstr, 'z', sizeof(longstr) - 1);
    longstr[4096] = 0;
    CHECK(fd_compare(1, longstr, 0, longstr));
    return (1);
}

static int test_putendl_fd_cases(void)
{
    CHECK(fd_compare(2, "", 0, "\n"));
    CHECK(fd_compare(2, "42", 0, "42\n"));
    CHECK(fd_compare(2, "a\nb", 0, "a\nb\n"));
    return (1);
}

static int test_putnbr_fd_cases(void)
{
    int nums[] = {0, 1, -1, 42, -42, INT_MIN, INT_MAX, 10000,
        -10000, 1000000000, -1000000000};
    char expected[64];
    size_t i;
    int n;

    i = 0;
    while (i < sizeof(nums) / sizeof(nums[0]))
    {
        snprintf(expected, sizeof(expected), "%d", nums[i]);
        CHECK(fd_compare(3, "", nums[i], expected));
        i++;
    }
    n = 0;
    while (n < 500)
    {
        i = next_random();
        snprintf(expected, sizeof(expected), "%d", (int)i);
        CHECK(fd_compare(3, "", (int)i, expected));
        n++;
    }
    return (1);
}

/* ---------------- 9 linked-list functions ---------------- */

static void del_count_free(void *content)
{
    g_del_calls++;
    free(content);
}

static void add_ten(void *content)
{
    g_iter_calls++;
    if (content)
        *(int *)content += 10;
}

static void *map_double(void *content)
{
    int *mapped;

    g_map_calls++;
    mapped = malloc(sizeof(*mapped));
    if (!mapped)
        return (NULL);
    *mapped = (*(int *)content) * 2;
    return (mapped);
}

static void *map_null(void *content)
{
    (void)content;
    return (NULL);
}

static int test_lstnew_content(void)
{
    int number;
    t_list *a;
    t_list *b;
    t_list *c;

    number = 1337;
    a = ft_lstnew(&number);
    b = ft_lstnew(NULL);
    c = ft_lstnew("literal");
    CHECK(a != NULL && b != NULL && c != NULL);
    CHECK(a != b && a != c && b != c);
    CHECK(a->content == &number && a->next == NULL);
    CHECK(b->content == NULL && b->next == NULL);
    CHECK(c->content != NULL && c->next == NULL);
    free(a);
    free(b);
    free(c);
    return (1);
}

static int test_lstadd_front_order(void)
{
    t_list *head;
    t_list *a;
    t_list *b;
    t_list *c;

    head = NULL;
    a = ft_lstnew("A");
    b = ft_lstnew("B");
    c = ft_lstnew("C");
    CHECK(a && b && c);
    ft_lstadd_front(&head, a);
    CHECK(head == a && a->next == NULL);
    ft_lstadd_front(&head, b);
    CHECK(head == b && b->next == a && a->next == NULL);
    ft_lstadd_front(&head, c);
    CHECK(head == c && c->next == b && b->next == a);
    CHECK(a->next == NULL);
    free(a);
    free(b);
    free(c);
    return (1);
}

static int test_lstsize_lengths(void)
{
    t_list nodes[300];
    t_list *head;
    size_t i;

    CHECK(ft_lstsize(NULL) == 0);
    i = 0;
    while (i < 300)
    {
        nodes[i].content = &nodes[i];
        nodes[i].next = NULL;
        if (i)
            nodes[i - 1].next = &nodes[i];
        head = &nodes[0];
        CHECK(ft_lstsize(head) == i + 1);
        CHECK(head == nodes);
        i++;
    }
    return (1);
}

static int test_lstlast_lengths(void)
{
    t_list nodes[300];
    size_t i;

    CHECK(ft_lstlast(NULL) == NULL);
    i = 0;
    while (i < 300)
    {
        nodes[i].next = NULL;
        nodes[i].content = NULL;
        if (i)
            nodes[i - 1].next = &nodes[i];
        CHECK(ft_lstlast(nodes) == &nodes[i]);
        i++;
    }
    CHECK(nodes[299].next == NULL);
    return (1);
}

static int test_lstadd_back_order(void)
{
    t_list *head;
    t_list nodes[250];
    size_t i;
    size_t j;
    t_list *cur;

    head = NULL;
    i = 0;
    while (i < 250)
    {
        nodes[i].content = &nodes[i];
        nodes[i].next = NULL;
        ft_lstadd_back(&head, &nodes[i]);
        CHECK(head == &nodes[0]);
        CHECK(ft_lstlast(head) == &nodes[i]);
        CHECK(ft_lstsize(head) == i + 1);
        i++;
    }
    cur = head;
    j = 0;
    while (j < 250)
    {
        CHECK(cur == &nodes[j]);
        cur = cur->next;
        j++;
    }
    CHECK(cur == NULL);
    return (1);
}

static int test_lstdelone_one_only(void)
{
    t_list *a;
    t_list *b;
    int *value;

    value = malloc(sizeof(int));
    CHECK(value != NULL);
    *value = 42;
    a = ft_lstnew(value);
    b = ft_lstnew(NULL);
    CHECK(a && b);
    a->next = b;
    g_del_calls = 0;
    ft_lstdelone(a, del_count_free);
    CHECK(g_del_calls == 1);
    CHECK(b->next == NULL && b->content == NULL);
    free(b);
    return (1);
}

static int test_lstclear_many(void)
{
    t_list *head;
    t_list *node;
    int *value;
    int i;

    head = NULL;
    g_del_calls = 0;
    ft_lstclear(&head, del_count_free);
    CHECK(head == NULL && g_del_calls == 0);
    i = 0;
    while (i < 200)
    {
        value = malloc(sizeof(int));
        CHECK(value != NULL);
        *value = i;
        node = ft_lstnew(value);
        CHECK(node != NULL);
        ft_lstadd_back(&head, node);
        i++;
    }
    ft_lstclear(&head, del_count_free);
    CHECK(head == NULL);
    CHECK(g_del_calls == 200);
    return (1);
}

static int test_lstiter_all(void)
{
    t_list nodes[200];
    int values[200];
    size_t i;

    g_iter_calls = 0;
    ft_lstiter(NULL, add_ten);
    CHECK(g_iter_calls == 0);
    i = 0;
    while (i < 200)
    {
        values[i] = (int)i;
        nodes[i].content = &values[i];
        nodes[i].next = i + 1 < 200 ? &nodes[i + 1] : NULL;
        i++;
    }
    ft_lstiter(nodes, add_ten);
    CHECK(g_iter_calls == 200);
    i = 0;
    while (i < 200)
    {
        CHECK(values[i] == (int)i + 10);
        CHECK(nodes[i].next == (i + 1 < 200 ? &nodes[i + 1] : NULL));
        i++;
    }
    return (1);
}

static int test_lstmap_deep_nodes(void)
{
    t_list original[100];
    int vals[100];
    t_list *mapped;
    t_list *cur;
    size_t i;

    i = 0;
    while (i < 100)
    {
        vals[i] = (int)i;
        original[i].content = &vals[i];
        original[i].next = i + 1 < 100 ? &original[i + 1] : NULL;
        i++;
    }
    g_map_calls = 0;
    g_del_calls = 0;
    mapped = ft_lstmap(original, map_double, del_count_free);
    CHECK(mapped != NULL && mapped != original);
    CHECK(ft_lstsize(mapped) == 100);
    CHECK(g_map_calls == 100);
    cur = mapped;
    i = 0;
    while (i < 100)
    {
        CHECK(cur != &original[i]);
        CHECK(cur->content != original[i].content);
        CHECK(*(int *)cur->content == (int)i * 2);
        CHECK(vals[i] == (int)i);
        cur = cur->next;
        i++;
    }
    CHECK(cur == NULL);
    ft_lstclear(&mapped, del_count_free);
    CHECK(mapped == NULL && g_del_calls == 100);
    return (1);
}

static int test_lstmap_empty_and_null_content(void)
{
    t_list *original;
    t_list *mapped;

    CHECK(ft_lstmap(NULL, map_double, del_count_free) == NULL);
    original = ft_lstnew(NULL);
    CHECK(original != NULL);
    mapped = ft_lstmap(original, map_null, del_count_free);
    CHECK(mapped != NULL);
    CHECK(mapped != original);
    CHECK(mapped->content == NULL && mapped->next == NULL);
    free(original);
    ft_lstclear(&mapped, del_count_free);
    CHECK(mapped == NULL);
    return (1);
}

/* Optional malloc failure tests, enabled by GNU ld --wrap=malloc. */
#ifdef TEST_MALLOC_FAILURE
static int g_fail_at;
static int g_malloc_calls;
void *__real_malloc(size_t size);

void *__wrap_malloc(size_t size)
{
    if (g_fail_at > 0)
    {
        g_malloc_calls++;
        if (g_malloc_calls == g_fail_at)
            return (NULL);
    }
    return (__real_malloc(size));
}

static void set_malloc_fail(int at)
{
    g_malloc_calls = 0;
    g_fail_at = at;
}

static int test_split_failure_cleanup(void)
{
    char **result;
    int i;

    i = 1;
    while (i <= 5)
    {
        set_malloc_fail(i);
        result = ft_split("one,two,three,four", ',');
        set_malloc_fail(0);
        CHECK(result == NULL);
        i++;
    }
    return (1);
}

static int test_strdup_failure(void)
{
    char *p;

    set_malloc_fail(1);
    p = ft_strdup("1337");
    set_malloc_fail(0);
    CHECK(p == NULL);
    return (1);
}

static int test_substr_failure(void)
{
    char *p;

    set_malloc_fail(1);
    p = ft_substr("abcdef", 1, 2);
    set_malloc_fail(0);
    CHECK(p == NULL);
    return (1);
}

static int test_strjoin_failure(void)
{
    char *p;

    set_malloc_fail(1);
    p = ft_strjoin("a", "b");
    set_malloc_fail(0);
    CHECK(p == NULL);
    return (1);
}

static int test_strtrim_failure(void)
{
    char *p;

    set_malloc_fail(1);
    p = ft_strtrim(" 42 ", " ");
    set_malloc_fail(0);
    CHECK(p == NULL);
    return (1);
}

static int test_itoa_failure(void)
{
    char *p;

    set_malloc_fail(1);
    p = ft_itoa(INT_MIN);
    set_malloc_fail(0);
    CHECK(p == NULL);
    return (1);
}

static int test_strmapi_failure(void)
{
    char *p;

    set_malloc_fail(1);
    p = ft_strmapi("42", change_even);
    set_malloc_fail(0);
    CHECK(p == NULL);
    return (1);
}

static int test_lstnew_failure(void)
{
    t_list *node;

    set_malloc_fail(1);
    node = ft_lstnew("hello");
    set_malloc_fail(0);
    CHECK(node == NULL);
    return (1);
}

static int test_lstmap_failure_cleanup(void)
{
    t_list original[3];
    int values[3] = {1, 2, 3};
    t_list *result;
    int fail;
    int i;

    i = 0;
    while (i < 3)
    {
        original[i].content = &values[i];
        original[i].next = i < 2 ? &original[i + 1] : NULL;
        i++;
    }
    fail = 2;
    while (fail <= 6)
    {
        g_del_calls = 0;
        g_map_calls = 0;
        set_malloc_fail(fail);
        result = ft_lstmap(original, map_double, del_count_free);
        set_malloc_fail(0);
        CHECK(result == NULL);
        CHECK(g_del_calls == fail / 2);
        CHECK(g_map_calls == fail / 2);
        CHECK(values[0] == 1 && values[1] == 2 && values[2] == 3);
        fail += 2;
    }
    return (1);
}
#endif

/* ---------------- Runner: independent process per case ---------------- */

typedef int (*t_test_fn)(void);

typedef struct s_test
{
    const char *func;
    const char *label;
    t_test_fn test;
} t_test;

static int run_one(const t_test *test)
{
    pid_t pid;
    int status;

    fflush(stdout);
    pid = fork();
    if (pid == -1)
        return (4);
    if (pid == 0)
    {
        alarm(8);
        _exit(test->test() ? 0 : 1);
    }
    if (waitpid(pid, &status, 0) != pid)
        return (4);
    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGALRM)
            return (3);
        return (2);
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        return (0);
    return (1);
}

int main(int argc, char **argv)
{
    const t_test tests[] = {
        CASE("ft_isalpha", "full byte range / 0-or-1", test_isalpha_all),
        CASE("ft_isdigit", "full byte range / 0-or-1", test_isdigit_all),
        CASE("ft_isalnum", "full byte range / 0-or-1", test_isalnum_all),
        CASE("ft_isascii", "negative and high boundary", test_isascii_all),
        CASE("ft_isprint", "ASCII boundaries / DEL", test_isprint_all),
        CASE("ft_strlen", "empty / embedded NUL / 4096", test_strlen_limits),
        CASE("ft_memset", "sizes / offsets / byte truncation", test_memset_sweep),
        CASE("ft_bzero", "guarded sizes and offsets", test_bzero_sweep),
        CASE("ft_memcpy", "all sizes / binary / guards", test_memcpy_sweep),
        CASE("ft_memmove", "overlap both directions / same ptr", test_memmove_overlap),
        CASE("ft_strlcpy", "all sizes / truncated and full", test_strlcpy_boundaries),
        CASE("ft_strlcat", "all capacities / unterminated prefix", test_strlcat_boundaries),
        CASE("ft_toupper", "0..255 / EOF", test_toupper_all),
        CASE("ft_tolower", "0..255 / EOF", test_tolower_all),
        CASE("ft_strchr", "0..255 / embedded NUL", test_strchr_all),
        CASE("ft_strrchr", "0..255 / repeated chars", test_strrchr_all),
        CASE("ft_strncmp", "2k randomized strings / lengths", test_strncmp_sweep),
        CASE("ft_memchr", "all lengths and byte values", test_memchr_sweep),
        CASE("ft_memcmp", "2k randomized buffers / signed bytes", test_memcmp_sweep),
        CASE("ft_strnstr", "every search window", test_strnstr_boundaries),
        CASE("ft_strnstr", "3k randomized searches", test_strnstr_random),
        CASE("ft_atoi", "signs / whitespace / INT limits", test_atoi_boundaries),
        CASE("ft_atoi", "3k random valid integer strings", test_atoi_random),
        CASE("ft_calloc", "zero-initialized 1..64 x 1..64", test_calloc_zeroing),
        CASE("ft_calloc", "zero-size distinct / overflow", test_calloc_zero_and_overflow),
        CASE("ft_strdup", "empty / embedded NUL / deep copy", test_strdup_cases),
#ifdef TEST_MALLOC_FAILURE
        CASE("ft_strdup", "forced allocation failure", test_strdup_failure),
#endif
        CASE("ft_substr", "start / len / UINT_MAX", test_substr_edges),
        CASE("ft_substr", "3k randomized start/length", test_substr_random),
#ifdef TEST_MALLOC_FAILURE
        CASE("ft_substr", "forced allocation failure", test_substr_failure),
#endif
        CASE("ft_strjoin", "empty / 128 length combinations", test_strjoin_edges),
#ifdef TEST_MALLOC_FAILURE
        CASE("ft_strjoin", "forced allocation failure", test_strjoin_failure),
#endif
        CASE("ft_strtrim", "empty / all trimmed / sets", test_strtrim_edges),
        CASE("ft_strtrim", "2k randomized trims", test_strtrim_random),
#ifdef TEST_MALLOC_FAILURE
        CASE("ft_strtrim", "forced allocation failure", test_strtrim_failure),
#endif
        CASE("ft_split", "empty / repeated delimiters / NUL", test_split_edges),
        CASE("ft_split", "250 tokens", test_split_many),
        CASE("ft_split", "2048-byte and 1500-byte tokens", test_split_long_tokens),
#ifdef TEST_MALLOC_FAILURE
        CASE("ft_split", "forced malloc failures 1..5", test_split_failure_cleanup),
#endif
        CASE("ft_itoa", "INT_MIN / INT_MAX / signed", test_itoa_limits),
        CASE("ft_itoa", "10k randomized integers", test_itoa_random),
#ifdef TEST_MALLOC_FAILURE
        CASE("ft_itoa", "forced allocation failure", test_itoa_failure),
#endif
        CASE("ft_strmapi", "empty / indices / 511 characters", test_strmapi_cases),
#ifdef TEST_MALLOC_FAILURE
        CASE("ft_strmapi", "forced allocation failure", test_strmapi_failure),
#endif
        CASE("ft_striteri", "index mutation / 511 characters", test_striteri_cases),
        CASE("ft_putchar_fd", "all printable and control bytes", test_putchar_fd_cases),
        CASE("ft_putchar_fd", "binary 0..255 (including NUL)", test_putchar_fd_binary),
        CASE("ft_putstr_fd", "empty / embedded NUL / 4096", test_putstr_fd_cases),
        CASE("ft_putendl_fd", "empty / newline / multiline", test_putendl_fd_cases),
        CASE("ft_putnbr_fd", "INT bounds / 500 random values", test_putnbr_fd_cases),
        CASE("ft_lstnew", "content pointer / NULL / next", test_lstnew_content),
#ifdef TEST_MALLOC_FAILURE
        CASE("ft_lstnew", "forced malloc failure", test_lstnew_failure),
#endif
        CASE("ft_lstadd_front", "head and ordering", test_lstadd_front_order),
        CASE("ft_lstsize", "empty / 300 growing nodes", test_lstsize_lengths),
        CASE("ft_lstlast", "empty / 300 growing nodes", test_lstlast_lengths),
        CASE("ft_lstadd_back", "250 inserts / ordering / cycles", test_lstadd_back_order),
        CASE("ft_lstdelone", "delete only one / callback", test_lstdelone_one_only),
        CASE("ft_lstclear", "empty / 200 allocations / head NULL", test_lstclear_many),
        CASE("ft_lstiter", "empty / mutate 200 / links intact", test_lstiter_all),
        CASE("ft_lstmap", "100 new nodes / deep content", test_lstmap_deep_nodes),
        CASE("ft_lstmap", "empty and NULL content", test_lstmap_empty_and_null_content),
#ifdef TEST_MALLOC_FAILURE
        CASE("ft_lstmap", "forced node failures and cleanup", test_lstmap_failure_cleanup),
#endif
    };
    size_t count;
    size_t i;
    int status;
    int passed;
    int failed;
    int verbose;
    int function_count;
    int function_passed;
    const char *last;

    setlocale(LC_CTYPE, "C");
    setvbuf(stdout, NULL, _IONBF, 0);
    verbose = (argc == 1 || strcmp(argv[1], "--brief") != 0);
    count = sizeof(tests) / sizeof(tests[0]);
    passed = 0;
    failed = 0;
    function_count = 0;
    function_passed = 1;
    last = NULL;
    printf("\n========== 1337 LIBFT v19.3 HARD TESTER ==========\n");
#ifdef TEST_MALLOC_FAILURE
    printf("Forced malloc failure mode: ENABLED\n");
#else
    printf("Forced malloc failure mode: OFF (see file header)\n");
#endif
    i = 0;
    while (i < count)
    {
        if (!last || strcmp(last, tests[i].func))
        {
            if (last)
                printf("%-19s => %s\n", last,
                    function_passed ? "OK" : "KO");
            last = tests[i].func;
            function_count++;
            function_passed = 1;
        }
        status = run_one(&tests[i]);
        if (verbose || status != 0)
            printf("  %-19s %-42s %s%s\n", tests[i].func,
                tests[i].label, status == 0 ? "OK" : "KO",
                status == 2 ? " (CRASH)" :
                (status == 3 ? " (TIMEOUT)" : (status == 4 ? " (RUNNER ERROR)" : "")));
        if (status == 0)
            passed++;
        else
        {
            failed++;
            function_passed = 0;
        }
        i++;
    }
    if (last)
        printf("%-19s => %s\n", last,
            function_passed ? "OK" : "KO");
    printf("\n============= FINAL RESULT =============\n");
    printf("Functions covered: %d / 43\n", function_count);
    printf("Passed test groups: %d / %zu\n", passed, count);
    printf("Failed test groups: %d\n", failed);
    if (!failed && function_count == 43)
    {
        puts("ALL TEST GROUPS: OK (not a guarantee of evaluator acceptance)");
        return (0);
    }
    puts("RESULT: KO - inspect failed cases above");
    return (1);
}
