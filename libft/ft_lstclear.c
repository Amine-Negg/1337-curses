/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 23:49:08 by mohanegg          #+#    #+#             */
/*   Updated: 2026/10/29 00:43:52 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nx;

	if (!lst)
		return ;
	while (*lst)
	{
		nx = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = nx;
	}
}
