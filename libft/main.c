#include "libft.h"
#include <stdio.h>

int main(void)
{
    printf("this is test for memset : \n\n\n");
    char str[] = "Hello";

    ft_memset(str, 'A', 3);
    printf("%s\n", str);

    printf("_________________\n");
    printf("\n\n");
    printf("this is test for memcpy : \n\n\n");

    char src[] = "test";
    char dest[10] = {0};

    printf("this is the dest before memcpy (%s) \n", dest);

    ft_memcpy(dest, src ,4);
    printf("this is the dest: (%s) \n and this is the src: (%s)\n\n", dest, src);



    printf("_________________\n");
    printf("\n\n");
    printf("this is test for memchr : \n\n\n");

    char jh[] = "amine neggaoui";

    ft_memchr(jh, 'n', 15);

    printf("%p\n", jh);

    printf("_________________\n");
    printf("\n\n");
    printf("this is test for memcmp : \n\n\n");

    char cmp[] = "TEST";
    char cmp1[] = "TESh";

    int res;

    printf("this is the s1 : %s \nand this is s2 : %s \n\n\n", cmp, cmp1);

    res = ft_memcmp(cmp, cmp1, 5);

    printf("\n this is the cmp s1 and s2 : %d\n\n\n", res);
    

        printf("_________________\n");
    printf("\n\n");
    printf("this is test for strchr : \n\n\n");

    char *sttt = "TEST";

    


    char *yyy;
    yyy = ft_strchr(sttt, 'O');

    printf("%p \n", yyy);
    printf("%c \n", *yyy);


    return (0);
}