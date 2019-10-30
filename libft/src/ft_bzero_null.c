/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 12:55:32 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/07/12 12:55:47 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero_null(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	while (n > 0)
	{
		str[i] = '\0';
		i++;
		n--;
	}
}
