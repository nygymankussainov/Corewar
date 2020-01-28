/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_name.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:01:05 by egiant            #+#    #+#             */
/*   Updated: 2019/12/05 17:17:46 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int				is_name(char *str)
{
	char		*ptr;

	if (!(ptr = ft_strstr(str, ".cor")))
		invalid_file_name(str);
	return (1);
}
