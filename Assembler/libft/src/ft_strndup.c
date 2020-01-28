/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:34:01 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/03 18:48:43 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && i < n)
		i++;
	if (!(result = ft_memalloc(i + 1)))
		return (NULL);
	while (s1[j] && j < n)
	{
		result[j] = s1[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}
