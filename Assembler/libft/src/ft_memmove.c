/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:35:22 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/25 23:34:29 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*s1;
	const unsigned char	*s2;
	size_t				i;

	s1 = (unsigned char *)dst;
	s2 = (const unsigned char *)src;
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s2 < s1)
	{
		while (i < len)
		{
			s1[len - 1] = s2[len - 1];
			len--;
		}
	}
	while (len > 0)
	{
		s1[i] = s2[i];
		i++;
		len--;
	}
	return (s1);
}
