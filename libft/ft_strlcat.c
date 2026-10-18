/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 18:49:49 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/18 20:13:22 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (j < dstsize && dst[j] != '\0')
    {
	    j++;
    }
    while (src[i] != '\0' && i < dstsize)
    {
        dst[j] = src[i];
        i++;
        j++;
    }
    while (dst[j] != '\0')
    {
        if (dstsize > i)
        {
            dst[j] ='\0';
        }
        j++;
    }
    return (dst);
}