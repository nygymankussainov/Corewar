/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:29:38 by egiant            #+#    #+#             */
/*   Updated: 2019/09/10 15:31:31 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_istrstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	if (needle[0] == '\0')
		return (-1);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j])
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
		}
		if (needle[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}
