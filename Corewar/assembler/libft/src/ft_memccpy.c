/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 19:35:59 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/25 23:18:48 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*s1;
	unsigned const char	*s2;
	unsigned char		uc;
	size_t				i;

	uc = (unsigned char)c;
	s1 = (unsigned char *)dst;
	s2 = (unsigned const char *)src;
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		if (s1[i] == uc)
			return (((void *)(s1 + i + 1)));
		i++;
	}
	return (NULL);
}
