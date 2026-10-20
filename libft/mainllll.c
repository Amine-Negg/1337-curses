#include "libft.h"
#include <stdio.h>

int main(void)
{
	char src[] = "YUHNB";
	char dest[2] = {0};

	ft_memcpy(dest, src, 5);
	printf("this is the dest after the memcpy : %s  ", dest);
}
