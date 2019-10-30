/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_doubles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 21:22:06 by screight          #+#    #+#             */
/*   Updated: 2019/08/05 22:35:06 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_get_decimal(char **mant, t_dbl *dnum, t_spec *argument)
{
	int		exp;
	int		pow;
	char	*tmp;
	int		s;

	s = 0;
	dnum->sign = ((dnum->d.binary >> 63) & 1u) ? -1 : 1;
	tmp = dnum->exponent;
	ft_get_exponent(dnum->d.binary, &tmp, 63);
	exp = ft_exponent_to_decimal(dnum->exponent);
	pow = exp - 1023;
	if (exp == 0)
		pow = -1022;
	tmp = dnum->mantis;
	ft_get_binary(dnum->d.binary, &tmp, 52, exp);
	if ((s = ft_handle_zero(dnum->exponent, dnum->mantis, argument,
							dnum->sign)) != -1)
		return (s);
	if (dnum->d.num * 10 == dnum->d.num)
		return (ft_handle_inf(argument, dnum->sign));
	if (dnum->d.num != dnum->d.num)
		return (ft_handle_nan(argument, 0));
	*mant = ft_mantis_to_decimal(dnum->mantis, pow, 53, argument->precision);
	return (s);
}

int			ft_get_long_decimal(char **mant, t_ldbl *ldnum, t_spec *argument)
{
	int		exp;
	int		pow;
	char	*tmp;
	int		s;

	s = 0;
	ldnum->sign = ((ldnum->ld.binary.fragm2 >> 15) & 1u) ? -1 : 1;
	tmp = ldnum->exponent;
	ft_get_binary(ldnum->ld.binary.fragm2, &tmp, 15, 33000);
	exp = ft_exponent_to_decimal((ldnum)->exponent);
	pow = exp - 16383;
	if (exp == 0)
		pow = -16382;
	tmp = ldnum->mantis;
	ft_get_binary(ldnum->ld.binary.fragm1, &tmp, 64, 33000);
	if ((s = ft_handle_zero(ldnum->exponent, ldnum->mantis, argument,
							ldnum->sign)) != -1)
		return (s);
	if (ldnum->ld.num * 10 == ldnum->ld.num)
		return (ft_handle_inf(argument, ldnum->sign));
	if (ldnum->ld.num != ldnum->ld.num)
		return (ft_handle_nan(argument, 0));
	*mant = ft_mantis_to_decimal(ldnum->mantis, pow, 64, argument->precision);
	return (s);
}

int			ft_handle_double(char **snum, t_spec *argument, va_list arg)
{
	t_dbl	*dnum;
	int		ret;
	int		sign;

	if (!(dnum = (t_dbl *)malloc(sizeof(t_dbl))))
		return (0);
	dnum->d.num = va_arg(arg, double);
	ret = ft_get_decimal(snum, dnum, argument);
	sign = dnum->sign;
	free(dnum);
	if (argument->type == 'f' && ret == -1)
		ret = (ft_output_f(*snum, argument, sign, 0));
	return (ret);
}

int			ft_handle_long_double(char **snum, t_spec *argument, va_list arg)
{
	t_ldbl	*ldnum;
	int		ret;
	int		sign;

	if (!(ldnum = (t_ldbl *)malloc(sizeof(t_ldbl))))
		return (0);
	ldnum->ld.binary.fragm1 = 0;
	ldnum->ld.binary.fragm2 = 0;
	ldnum->ld.num = va_arg(arg, long double);
	ret = ft_get_long_decimal(snum, ldnum, argument);
	sign = ldnum->sign;
	free(ldnum);
	if (argument->type == 'f' && ret == -1)
		ret = (ft_output_f(*snum, argument, sign, 0));
	return (ret);
}
