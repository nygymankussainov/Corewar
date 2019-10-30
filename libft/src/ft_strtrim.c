/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:37:43 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/03 18:26:26 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s) - 1;
	i = ft_skip_whitesp(s);
	if (!s[i])
		return (ft_strnew(0));
	while (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')
		j--;
	if (!(result = ft_memalloc(j - i + 2)))
		return (NULL);
	while (i <= j)
	{
		result[k] = s[i];
		k++;
		i++;
	}
	result[k] = '\0';
	return (result);
}
