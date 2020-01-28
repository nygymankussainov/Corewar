/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:55:42 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/24 19:59:10 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*s1;
	unsigned char		uc;

	s1 = (unsigned const char *)s;
	uc = (unsigned char)c;
	while (n--)
	{
		if (*s1 != uc)
			s1++;
		else
			return ((void *)s1);
	}
	return (0);
}
