/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:28:46 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/01 16:18:05 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		validate_file(char *file)
{
	int		len;
	int		fd;

	len = ft_strlen(file);
	fd = open(file, O_RDONLY);
	if (fd < 0 || file[len - 1] != 's' || file[len - 2] != '.')
	{
		if (fd < 0)
			perror("Error");
		else
			putstrerr("Invalid file name. Missing .s extension.\n");
		return (0);
	}
	return (fd);
}
