/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:19:14 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/27 13:52:48 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int	i;

	if (!s1 && !s2)
		return (1);
	else if (!s1 || !s2)
		return (0);
	i = ft_strcmp(s1, s2);
	if (i == 0)
		return (1);
	return (0);
}
