/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 17:40:23 by screight          #+#    #+#             */
/*   Updated: 2019/10/25 17:01:29 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_wordslen(const char *str, char c)
{
	int len;

	len = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == c)
			str++;
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}

static int		ft_wordsnum(const char *str, char c)
{
	int num;

	num = 0;
	if (!str)
		return (0);
	if (*str && *str != c)
	{
		num++;
		str++;
	}
	while (*str != '\0')
	{
		if (*str != c && *(str - 1) == c)
		{
			num++;
			str++;
		}
		else
			str++;
	}
	return (num);
}

static void		ft_cpy(char *dst, const char *src, int i)
{
	int n;

	n = 0;
	while (n < i)
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
}

static int		ft_make(char **new, const char *str, char c, int n)
{
	int i;
	int start;
	int end;

	start = 0;
	i = 0;
	while (i < n && str[start] != '\0')
	{
		while (str[start] == c)
			start++;
		end = start;
		while (str[end] && str[end] != c)
			end++;
		if (!(new[i] = ft_strnew(end - start)))
		{
			while (--i >= 0)
				free(new[i]);
			return (0);
		}
		ft_cpy(new[i], &str[start], (end - start));
		start = end + 1;
		i++;
	}
	return (1);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**new;
	int		count;
	int		i;

	if (!s)
		return (NULL);
	count = ft_wordslen(s, c);
	i = ft_wordsnum(s, c);
	if (!count)
	{
		if (!(new = malloc(sizeof(*new))))
			return (NULL);
		new[0] = NULL;
		return (new);
	}
	if (!(new = (char**)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	if (!ft_make(new, s, c, i))
	{
		free(new);
		return (NULL);
	}
	new[i] = 0;
	return (new);
}
