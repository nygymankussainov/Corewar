/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:54:50 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/25 23:27:17 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	result;
	size_t	i;

	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (size <= dlen)
		result = size + slen;
	else
		result = slen + dlen;
	while (src[i] && dlen + 1 < size)
	{
		dst[dlen] = src[i];
		dlen++;
		i++;
	}
	dst[dlen] = '\0';
	return (result);
}
