/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:13:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/26 10:00:35 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	*ft_range(size_t min, size_t max)
{
	size_t		*arr;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (min >= max || !(arr = ft_memalloc(max - min)))
		return (NULL);
	while (min < max)
	{
		arr[i] = min;
		i++;
		min++;
	}
	return (arr);
}
