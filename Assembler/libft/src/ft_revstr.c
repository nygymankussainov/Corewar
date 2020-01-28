/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 11:09:37 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/07/31 16:06:22 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_revstr(char *str)
{
	int		i;
	char	c;
	char	*result;

	result = str;
	i = ft_strlen(str);
	while (i >= 2)
	{
		c = *str;
		*str = str[i - 1];
		str[i - 1] = c;
		str++;
		i -= 2;
	}
	return (result);
}
