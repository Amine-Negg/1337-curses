/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 07:16:53 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/28 07:29:20 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_lstsize(t_list *lst)
{
	unsigned int	count;

	count = 0;
	if (!lst)
	{
		return (0);
	}
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
