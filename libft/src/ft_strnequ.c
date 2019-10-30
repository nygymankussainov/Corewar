/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:39:56 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/23 15:17:41 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int	i;

	if (n + 1 == 0)
		return (0);
	if (!s1 && !s2)
		return (1);
	else if (!s1 || !s2)
		return (0);
	i = ft_strncmp(s1, s2, n);
	if (i == 0)
		return (1);
	return (0);
}
