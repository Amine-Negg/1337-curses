/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 21:59:56 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/29 15:58:39 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jo;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	jo = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!jo)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		jo[j++] = s1[i++];
	i = 0;
	while (s2[i])
		jo[j++] = s2[i++];
	jo[j] = '\0';
	return (jo);
}
