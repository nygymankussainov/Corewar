/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longadd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:17:57 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/07/31 16:54:53 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	column_add(char *s1, char *s2, int l1, char **res1)
{
	int		l2;
	int		i;
	int		rem;
	int		sum;

	i = 0;
	rem = 0;
	l2 = ft_strlen(s2);
	while (i < l1)
	{
		sum = ((s1[i] - '0') + (s2[i] - '0')) + rem;
		(*res1)[i++] = (sum % 10) + '0';
		rem = sum / 10;
	}
	i = l1;
	while (i < l2)
	{
		sum = (s2[i] - '0') + rem;
		(*res1)[i++] = (sum % 10) + '0';
		rem = sum / 10;
	}
	*res1 = rem ? ft_realloc(*res1, l2 + 1) : *res1;
	(*res1)[l2] = rem ? rem + '0' : (*res1)[l2];
	(*res1)[l2 + rem] = '\0';
}

void	get_res(char **res1, char **res2, char **str1, char **str2)
{
	int		len;

	len = ft_strlen(*res1);
	free(*res2);
	if (!(*res2 = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return ;
	(*res1)[len] = '\0';
	(*res2)[len] = '\0';
	*res2 = ft_strncpy(*res2, *res1, len);
	free(*res1);
	free(*str1);
	free(*str2);
}

void	longadd(char *s1, char *s2, char **res2)
{
	char	*str1;
	char	*str2;
	int		l1;
	int		l2;
	char	*res1;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (!(str1 = (char *)ft_memalloc(sizeof(char) * (l1 + 1))) ||
		!(str2 = (char *)ft_memalloc(sizeof(char) * (l2 + 1))))
		return ;
	str1 = ft_strncpy(str1, s1, l1);
	str2 = ft_strncpy(str2, s2, l2);
	if (l1 > l2)
	{
		ft_swap_str(&str1, &str2);
		ft_swap(&l1, &l2);
	}
	ft_revstr(str1);
	ft_revstr(str2);
	if (!(res1 = (char *)ft_memalloc(sizeof(char) * (l2 + 1))))
		return ;
	column_add(str1, str2, l1, &res1);
	ft_revstr(res1);
	get_res(&res1, res2, &str1, &str2);
}
