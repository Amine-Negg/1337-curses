/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 02:50:59 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/18 02:58:37 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
    size_t  i;
    size_t  j;

    i = 0;

    if (little[0] == '\0')
    {
	    return ((char *)big);
    }
    while (big[i] != '\0' && i < len)
    {
        j = 0;
        while (little[j] != '\0' && )
        {
            j++;
        }
    }
}