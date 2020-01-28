/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:14:14 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/29 11:28:51 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*result;
	int		i;

	i = 0;
	if (!s || !(result = ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	while (s[i])
	{
		result[i] = f(s[i]);
		i++;
	}
	return (result);
}
