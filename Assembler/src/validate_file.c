/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:28:46 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/10 16:33:42 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	validate_file(char *file, t_major *major)
{
	int		len;

	len = ft_strlen(file);
	FD = open(file, O_RDONLY);
	if (FD < 0 || file[len - 1] != 's' || file[len - 2] != '.')
	{
		if (FD < 0)
			perror("Error");
		else
			putstrerr("Invalid file name. Missing .s extension\n");
		exit(1);
	}
	len--;
	while (file[len] && file[len] != '.')
		len--;
	file[len + 1] = '\0';
	major->filename = ft_strjoin(file, "cor", 0, 0);
}
