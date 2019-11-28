/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 14:51:13 by egiant            #+#    #+#             */
/*   Updated: 2019/10/25 18:41:26 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <float.h>
# include <math.h>
# include <locale.h>
# include <wctype.h>

typedef struct				s_valid
{
	short					flags;
	short					width;
	short					precision;
	short					size;
	short					type;
}							t_valid;

typedef struct				s_spec
{
	char					*flags;
	int						width;
	int						precision;
	char					*size;
	char					type;
}							t_spec;

typedef struct				s_long_double
{
	union					u_ldbl
	{
		long double			num;
		struct
		{
			unsigned long	fragm1;
			unsigned long	fragm2;
		}					binary;
	}						ld;
	char					mantis[64 + 1];
	char					exponent[15 + 1];
	int						sign;
}							t_ldbl;

typedef	struct				s_double
{
	char					mantis[53 + 1];
	char					exponent[11 + 1];
	int						sign;
	union					u_dbl
	{
		double				num;
		unsigned long		binary;
	}						d;
}							t_dbl;

int							ft_printf(const char *format, ...);
int							ft_get_flags(const char **str, t_spec *argument);
int							ft_valid_flags(t_spec *argument, int i);
int							ft_count_valid(t_spec *argument, char type,
											int *ef);
int							ft_edit_flags(t_spec *argument, char ch);
void						ft_ignored_zero(t_spec *argument);
void						ft_ignored_space(t_spec *argument);
int							ft_get_width(const char **str, t_spec *argument,
										va_list arg);
int							ft_get_precision(const char **str, t_spec *argument,
											va_list arg);
int							ft_get_type_size(const char **str,
											t_spec *argument);
int							ft_get_type(const char **str, t_spec *argument);
int							ft_solve_d(t_spec *argument, va_list arg);
int							ft_write_d_case1(t_spec *argument, char *number,
											int digits);
int							ft_write_d_case2(t_spec *argument, char *number,
											int digits);
int							ft_write_d_case3(t_spec *argument, char *number,
											int digits);
int							ft_solve_ox(t_spec *argument, va_list arg, int base,
										int reg);
int							ft_write_ox_case1(t_spec *argument, char *number,
											int digits, int registr);
int							ft_write_ox_case2(t_spec *argument, char *number,
											int digits, int registr);
int							ft_write_ox_case3(t_spec *argument, char *number,
											int digits, int registr);
int							ft_solve_u(t_spec *argument, va_list arg);
int							ft_write_u_case1(t_spec *argument, char *number,
											int digits);
int							ft_write_u_case2(t_spec *argument, char *number,
											int digits);
int							ft_solve_c(t_spec *argument, va_list arg);
int							ft_solve_s(t_spec *ar, va_list arg);
int							ft_write_utf(t_spec *argument, long sym, int min);
int							ft_bigc_width(t_spec *argument, int len);
int							ft_solve_p(t_spec *argument, va_list arg);
int							ft_valid_flags_c_s_p(t_spec *argument);
int							ft_solve_percent(t_spec *argument);
int							ft_solve_f(t_spec *argument, va_list arg);
int							ft_write_f(t_spec *argument, char *number,
										int digits, int lattice);
int							ft_output_f(char *snum, t_spec *argument, int sign,
										int z);
void						ft_get_binary(unsigned long binary, char **num,
										int start, int power);
void						ft_get_exponent(unsigned long binary, char **num,
										int start);
int							ft_exponent_to_decimal(char *num);
char						*ft_mantis_to_decimal(char *mantis, int pow,
											int len, int prec);
int							ft_handle_zero(char *exp, char *mant,
											t_spec *argument, int sign);
int							ft_handle_nan(t_spec *argument, int i);
int							ft_handle_inf(t_spec *argument, int sign);
char						*ft_get_fraction(char *bin, int len, int zs,
											int count);
char						*ft_get_ints(char *bin, int ints, int len,
										int sign1);
char						*ft_int_str_rev(char *str);
int							ft_handle_double(char **snum, t_spec *argument,
											va_list arg);
int							ft_handle_long_double(char **snum, t_spec *argument,
											va_list arg);

#endif
