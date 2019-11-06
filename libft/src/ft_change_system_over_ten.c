/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_system_over_ten.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:52:25 by egiant            #+#    #+#             */
/*   Updated: 2019/07/31 17:02:18 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_change_system_over_ten(unsigned long num, int base,
						int registr)
{
	int				i;
	int				n;
	char			*number;
	unsigned long	result;

	result = num;
	n = 1;
	while (num / base > 0 && ++n)
		num = num / base;
	if (!(number = (char*)malloc(sizeof(char) * (n + 1))))
		return (0);
	number[n--] = '\0';
	while (n >= 0)
	{
		i = result % base;
		if (i < 10)
			number[n--] = i + '0';
		else if (registr == 1)
			number[n--] = 65 + i % 10;
		else
			number[n--] = 97 + i % 10;
		result = result / base;
	}
	return (number);
}
