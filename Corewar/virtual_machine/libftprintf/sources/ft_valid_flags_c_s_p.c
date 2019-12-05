/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_flags_c_s_p.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 18:58:51 by screight          #+#    #+#             */
/*   Updated: 2019/08/05 22:37:14 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_valid_flags_c_s_p(t_spec *argument)
{
	if (!argument->flags)
		return (1);
	else if (argument->type == 'c' && !(argument->flags[0] == '-'))
		return (1);
	else if (argument->flags[0] == '-' || argument->flags[0] == '0')
		return (argument->flags[0] == '-') ? -1 : 2;
	return (0);
}
