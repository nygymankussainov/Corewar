/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:36:50 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/24 20:51:01 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	b;

	str = (0);
	b = (char)c;
	while (*s)
	{
		if (*s == b)
			str = (char *)s;
		s++;
	}
	if (str)
		return (str);
	if (!b)
		return ((char *)s);
	return (NULL);
}
