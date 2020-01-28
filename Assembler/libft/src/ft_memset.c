/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:40:25 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/25 23:20:20 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	char			*s;
	unsigned char	j;

	s = (char *)str;
	j = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		s[i] = j;
		i++;
	}
	return (s);
}
