/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_bytes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:02:21 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/01 18:48:27 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	*rev_bytes(char *str, int size)
{
	char	c;
	char	*result;

	result = str;
	while (size >= 2)
	{
		c = *str;
		*str = str[size - 1];
		str[size - 1] = c;
		str++;
		size -= 2;
	}
	return (result);
}
