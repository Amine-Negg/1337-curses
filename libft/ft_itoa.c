/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 22:05:48 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/24 22:05:51 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(long n)
{
	size_t	count;

	count = 1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nbr;
	size_t	len;
	size_t	sign;
	char	*str;

	nbr = n;
	sign = (nbr < 0);
	if (nbr < 0)
		nbr = -nbr;
	len = count_digits(nbr) + sign;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > sign)
	{
		str[--len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
