/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_u_case1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:56:51 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:38:05 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_write_u_case1(t_spec *argument, char *number, int digits)
{
	int		difference;

	difference = argument->precision - digits;
	while (difference-- > 0)
		write(1, "0", 1);
	while (*number != '\0')
		write(1, number++, 1);
	return (argument->precision >= digits) ? argument->precision : digits;
}
