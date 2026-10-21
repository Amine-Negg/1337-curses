#include "libft.h"
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("=== TOUPPER ===\n");
	printf("ft_toupper('a'): %d\n", ft_toupper('a'));
	printf("toupper('a'):    %d\n", toupper('a'));

	printf("\n=== NEGATIVE INPUT ===\n");
	printf("ft_toupper(-50): %d\n", ft_toupper(-50));

	printf("\n=== VALID UNSIGNED INPUT ===\n");
	printf("ft_toupper(206): %d\n", ft_toupper(206));
	printf("toupper(206):    %d\n", toupper(206));

	printf("\n=== EOF ===\n");
	printf("ft_toupper(EOF): %d\n", ft_toupper(EOF));
	printf("toupper(EOF):    %d\n", toupper(EOF));

	return (0);
}