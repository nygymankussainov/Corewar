/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:01:34 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:37:18 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_valid_flags(t_spec *arg, int i)
{
	int		count;
	char	*newflags;
	char	*ptr;
	int		ef;

	ef = 0;
	if (!arg->flags)
		return (1);
	ft_ignored_zero(arg);
	ft_ignored_space(arg);
	if (!(count = ft_count_valid(arg, arg->type, &ef)))
		ft_strdel(&(arg->flags));
	else if (count > 0)
	{
		if (!(newflags = (char*)malloc(sizeof(char) * (count + 1))))
			return (0);
		newflags[count--] = '\0';
		while (count >= 0)
			(arg->flags[i] != 'x') ? newflags[count--] = arg->flags[i++] : i++;
		ptr = arg->flags;
		arg->flags = newflags;
		free(ptr);
	}
	return (ef == -1) ? -1 : 1;
}
