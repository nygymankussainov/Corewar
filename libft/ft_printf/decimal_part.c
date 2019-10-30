/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:14:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/07/31 16:52:07 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_length(char *mant, int exp_i)
{
	int		i;
	int		j;

	i = -exp_i;
	j = 0;
	while (*mant)
	{
		if (*mant == '1')
		{
			j = i;
			if (*(mant + 1) == '\0')
				j++;
		}
		i++;
		mant++;
	}
	if (j == -exp_i)
		return (j);
	else if (j == 0)
		return (-exp_i);
	return (j + 1);
}

void	prepare_number(char *n1, char **res, int exp_i)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(n1);
	while (*n1)
	{
		while (j < -exp_i)
		{
			i++;
			j++;
		}
		(*res)[i] = *n1;
		i++;
		n1++;
	}
}

int		is_all_zeroes(char *mant)
{
	while (*mant)
	{
		if (*mant != '0')
			return (0);
		mant++;
	}
	return (1);
}

void	get_to_first_one(char **mant, int bigl, int *exp_i)
{
	while (**mant != '1')
	{
		(*mant)++;
		(*exp_i)--;
	}
	if (!bigl)
		(*mant)++;
}

int		decimal_part(char **integer, t_f f, t_flags *s)
{
	int		len;
	char	*res;
	char	*n1;
	char	*tmp_mant;

	if (f.isint && *f.mant && s->bigl)
		get_to_first_one(&f.mant, s->bigl, &f.exp_i);
	if ((!*f.mant || is_all_zeroes(f.mant)) && f.exp_i != -1022)
	{
		res = ft_strnew(0);
		return (print(&res, integer, s, f.sign));
	}
	if (f.isint && *f.mant && !s->bigl)
		get_to_first_one(&f.mant, s->bigl, &f.exp_i);
	f.mant += s->bigl ? 1 : 0;
	if (s->bigl && f.exp_i != -16382)
		tmp_mant = ft_strjoin(f.mant, "1", 0, 0);
	else
		tmp_mant = ft_strdup(f.mant);
	len = get_length(tmp_mant, f.exp_i);
	res = get_initial_number(len, f.exp_i, &n1);
	f.exp_i--;
	calculate_decimal(tmp_mant, &res, f.exp_i, &n1);
	free(tmp_mant);
	return (print(&res, integer, s, f.sign));
}
