/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:15:47 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/16 16:15:49 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*help;

	if (lst)
	{
		while (*lst)
		{
			help = (*lst)->next;
			ft_lstdelone(*lst, del);
			*(lst) = help;
		}	
	}
}
