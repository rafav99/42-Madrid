/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:16:11 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/16 16:16:13 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*aux;

	if (!lst)
		return (NULL);
	aux = ft_lstnew(f(lst->content));
	if (!aux)
		return (NULL);
	map = aux;
	lst = lst->next;
	while (lst)
	{
		map->next = ft_lstnew(f(lst->content));
		if (!map)
		{
			ft_lstclear(&aux, del);
			return (NULL);
		}
		map = map->next;
		lst = lst->next;
	}
	return (aux);
}
