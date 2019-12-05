/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_zero.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 20:11:39 by screight          #+#    #+#             */
/*   Updated: 2019/08/02 14:53:28 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_fill_zero(int len)
{
	int		i;
	char	*str;

	i = 0;
	if (len < 0)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
		str[i++] = '0';
	str[i] = '\0';
	return (str);
}
