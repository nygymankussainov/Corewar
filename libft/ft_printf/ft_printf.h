/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:02:01 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/30 19:38:02 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define F format

# include <stdio.h>
# include <stdarg.h>
# include "libft.h"

typedef struct		s_f
{
	char			*binary;
	short			sign;
	char			*exp;
	char			*mant;
	long double		db;
	int				exp_i;
	int				mant_i;
	short			isint;
}					t_f;

typedef struct		s_flags
{
	int				zero_padd;
	int				prec;
	int				width;
	int				whitesp;
	int				sign;
	char			conv;
	short			dot;
	short			bigl;
	short			h;
	short			l;
	short			m;
	short			z;
	short			zero;
	short			pos;
	short			neg;
	short			hash;
}					t_flags;

int					ft_printf(const char *format, ...);
int					find_conv(const char *s);
void				find_whitesp(const char **format, t_flags *s);
int					ft_conv_s(const char **format, va_list valist, t_flags *s);
int					ft_conv_c(const char **format, va_list valist, t_flags *s);
int					ft_conv_o(const char **format, va_list valist, t_flags *s);
int					ft_conv_p(const char **format, va_list valist, t_flags *s);
int					ft_conv_x(const char **format, va_list valist, t_flags *s);
int					ft_conv_d(const char **format, va_list valist, t_flags *s);
int					ft_conv_u(const char **format, va_list valist, t_flags *s);
int					ft_conv_f(const char **format, va_list valist, t_flags *s);
int					ft_number(const char **format, va_list valist, t_flags *s);
int					ft_symbol(const char **format, va_list valist, t_flags *is);
int					get_width(char *str);
int					width_for_f(char *str, t_flags *s, int ret);
int					width(char *str, t_flags *s, int len);
int					manage_width(char *str, t_flags *s);
int					print_zero_or_space(int width, int zero, int ret);
int					integer_part(t_f f, t_flags *s);
int					decimal_part(char **integer, t_f f, t_flags *s);
void				prepare_number(char *n1, char **res, int exp_i);
void				calculate_decimal(char *mant, char **res, int exp_i,
	char **n1);
char				*get_initial_number(int len, int exp_i, char **n1);
int					print(char **decimal, char **integer, t_flags *s,
	int sign);
int					get_width(char *str);
void				longadd(char *s1, char *s2, char **res2);
void				longmulti(char *a, const char *b, char **c);
void				longdiv(char *number, int divisor, char **res);
int					ft_conv_b(t_flags *s, t_f f);

#endif
