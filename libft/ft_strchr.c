/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:39:14 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/17 17:07:53 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
    size_t  i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c)
        {
            return ((char *)(s + i));
        }
        i++;
    }
    if (s[i] == '\0')
    {
        if (c == 0)
        {
            return ((char *)(s + i));
        }
    }
    
    return NULL;
}