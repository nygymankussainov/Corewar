/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:30:34 by egiant            #+#    #+#             */
/*   Updated: 2019/07/31 17:02:26 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_help(unsigned long result,
							unsigned long num, int n, int base)
{
	int					j;
	char				*number;
	unsigned long long	helper;

	helper = 0;
	j = 0;
	while (num > 0 && n++)
	{
		helper = helper * 10 + num % base;
		num = num / base;
	}
	if (!(number = (char*)malloc(sizeof(char) * (n + 1))))
		return (0);
	number[n] = '\0';
	while (helper > 0)
	{
		number[j++] = helper % 10 + '0';
		helper = helper / 10;
	}
	while (j < n)
	{
		number[j++] = result % 10 + '0';
		result = result / 10;
	}
	return (number);
}

char					*ft_change_system(unsigned long num, int base)
{
	int					i;
	int					n;
	unsigned long long	result;
	char				*number;

	result = 0;
	n = (num == 0) ? 1 : 0;
	while (num > 0)
	{
		if (result > 1844677407370955161)
			return (ft_help(result, num, n, base));
		result = result * 10 + num % base;
		num = num / base;
		n++;
	}
	if (!(number = (char*)malloc(sizeof(char) * (n + 1))))
		return (0);
	number[n--] = '\0';
	i = 0;
	while (n-- >= 0)
	{
		number[i++] = result % 10 + '0';
		result = result / 10;
	}
	return (number);
}
