/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 18:49:23 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/15 19:41:52 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
    size_t  i;
    size_t  len;
    unsigned char *d;
    const unsigned char *s;
    
    d = (unsigned char *)dest;
    s = (const unsigned char *)src;
    i = 0;
    len = 0;
    
    while (d > s)
    {
        
    }
    
}