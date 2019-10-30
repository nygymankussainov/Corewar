/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:32:19 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/27 19:27:39 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*first;

	if (!alst || !del)
		return ;
	if (*alst)
	{
		first = *alst;
		while (*alst)
		{
			first = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = first;
		}
		*alst = NULL;
	}
}
