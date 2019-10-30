/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longdiv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:39:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/07/31 15:14:25 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	longdiv(char *number, int divisor, char **res)
{
	int		len;
	int		i;
	char	*ans;
	int		idx;
	int		temp;

	idx = 0;
	temp = number[idx] - '0';
	while (temp < divisor)
		temp = temp * 10 + (number[++idx] - '0');
	len = ft_strlen(number);
	if (!(ans = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return ;
	i = 0;
	while (len > idx)
	{
		ans[i++] = (temp / divisor) + '0';
		temp = (temp % divisor) * 10 + number[++idx] - '0';
	}
	ans[0] = ft_strlen(ans) == 0 ? '0' : ans[0];
	free(*res);
	if (!(*res = (char *)ft_memalloc(sizeof(char) * (ft_strlen(ans) + 1))))
		return ;
	*res = ft_strcpy(*res, ans);
	free(ans);
}
