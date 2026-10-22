#include "libft.h"
#include <stdio.h>
int main()
{
	char s[5];
	printf("before :%s \n", s);
	ft_memset(s , 'H', 7);
	printf("after :%s \n", s);
}
