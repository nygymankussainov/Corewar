/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 21:39:28 by screight          #+#    #+#             */
/*   Updated: 2019/02/13 21:39:30 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*tmp;
	t_list	*head;

	if (!(lst) || !(f))
		return (NULL);
	tmp = f(lst);
	if (!(new_lst = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	lst = lst->next;
	head = new_lst;
	while (lst)
	{
		tmp = f(lst);
		if (!(new_lst->next = ft_lstnew(tmp->content, tmp->content_size)))
			return (NULL);
		lst = lst->next;
		new_lst = new_lst->next;
	}
	return (head);
}
