/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 21:59:28 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/28 22:59:37 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	int					results;
	const unsigned char	*ss;
	const unsigned char	*ss3;

	ss = (const unsigned char *) s1;
	ss3 = (const unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (ss[i] > ss3[i] || ss[i] < ss3[i])
		{
			results = ss[i] - ss3[i];
			return (results);
		}
		i++;
	}
	return (0);
}
