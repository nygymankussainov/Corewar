/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 15:07:23 by screight          #+#    #+#             */
/*   Updated: 2018/12/19 15:07:25 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int rez;

	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			rez = (unsigned char)*s1 - (unsigned char)*s2;
			return (rez);
		}
		s1++;
		s2++;
	}
	return (0);
}
