/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whitesp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 22:03:06 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/03 18:24:08 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_skip_whitesp(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\r' ||
				str[i] == '\t' || str[i] == '\v' || str[i] == '\f'))
		i++;
	return (i);
}
