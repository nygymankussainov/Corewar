/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 20:05:54 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/18 11:55:15 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	unsigned int i;
	unsigned int j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	j = 0;
	while (haystack[j] != '\0')
	{
		if (haystack[j] == needle[0])
		{
			i = 1;
			while (needle[i] != '\0' && haystack[i + j] == needle[i])
				i++;
			if (needle[i] == '\0')
				return ((char *)&haystack[j]);
		}
		j++;
	}
	return (0);
}
