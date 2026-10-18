/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 17:39:43 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/18 18:25:55 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t  i;

    i = 0;
    while (src[i] != '\0' && i + 1 < dstsize)
    {
        dst[i] = src[i];
        i++;
    }
    if (dstsize > 0)
    {
        dst[i] = '\0';
    }
    return (ft_strlen(src));
}