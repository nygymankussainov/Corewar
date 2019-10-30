/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:58:14 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/29 11:35:04 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(t_list *lst)
{
	while (lst)
	{
		free(lst);
		lst = NULL;
		lst = lst->next;
	}
	lst = NULL;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*first;

	if (!lst || !f)
		return (NULL);
	if (!(new = ft_lstnew((f(lst))->content, (f(lst))->content_size)))
	{
		ft_free(new);
		return (NULL);
	}
	first = new;
	lst = lst->next;
	while (lst)
	{
		if (!(new->next = ft_lstnew((f(lst))->content, (f(lst))->content_size)))
		{
			ft_free(first);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (first);
}
