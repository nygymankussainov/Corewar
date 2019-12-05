/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 15:09:22 by screight          #+#    #+#             */
/*   Updated: 2018/12/19 15:09:24 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		if (src[i] == '\0')
		{
			while (i < len)
			{
				dst[i] = '\0';
				i++;
			}
		}
		i++;
	}
	return (dst);
}
