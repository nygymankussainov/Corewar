/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:21:29 by egiant            #+#    #+#             */
/*   Updated: 2019/07/31 17:02:33 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_digits(char *number)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (number[i] == '-')
		i++;
	while (number[i])
	{
		len++;
		i++;
	}
	return (len);
}
