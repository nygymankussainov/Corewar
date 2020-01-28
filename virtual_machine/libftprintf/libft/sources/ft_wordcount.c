/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:07:54 by screight          #+#    #+#             */
/*   Updated: 2019/03/15 14:18:05 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wordcount(char *s, char c)
{
	int	wcount;
	int	i;

	i = 0;
	if (!s)
		return (0);
	wcount = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		while (s[i] != c && s[i])
			i++;
		wcount++;
	}
	return (wcount);
}
