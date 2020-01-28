/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 18:35:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/07/31 16:02:56 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*newptr;

	if (!size && ptr)
	{
		if (!(newptr = (char *)ft_memalloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return (newptr);
	}
	if (!(newptr = (char *)ft_memalloc(size + 1)))
		return (NULL);
	if (ptr)
	{
		ft_memcpy(newptr, (char *)ptr, size - 1);
		ft_memdel(&ptr);
	}
	newptr[size - 1] = '0';
	newptr[size] = '\0';
	return (newptr);
}
