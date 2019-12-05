/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 10:41:14 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/09 15:23:27 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*s1;
	const unsigned char	*s2;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	s1 = (unsigned char *)dst;
	s2 = (unsigned const char *)src;
	i = 0;
	while (n > 0)
	{
		s1[i] = s2[i];
		i++;
		n--;
	}
	return (s1);
}
