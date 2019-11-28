/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:49:05 by egiant            #+#    #+#             */
/*   Updated: 2019/11/28 16:21:57 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

uint8_t			get_core_number(t_core **cores)
{
	uint8_t		i;

	i = 0;
	while (cores[i] && i < 4)
		i++;
	if (i == 4)
		termination_with_error("Too many cores\n");
	return (i);
}

char			*concat_args(char **argv, int count)
{
	char		*res;
	uint16_t	size;
	uint8_t		i;

	i = 0;
	size = 0;
	while (++i < count)
		size += ft_strlen(argv[i]);
	if (!(res = (char*)ft_memalloc(size + 1)))
		termination_with_perror("Concat args error", ENOMEM);
	i = 0;
	while (++i < count)
		ft_strcat(res, argv[i]);
	return (res);
}

void 			process_dump_flag(t_corewar **vm, char *arg_str)
{
	if (arg_str == NULL || *arg_str == '\0' || ft_isdigit(*arg_str) == false)
		termination_with_error("There is no value for dump\n");
	(*vm)->dumps = ft_atoi(arg_str);
}

void			set_player_name(char *core_name, char *path)
{
	char	*needle;

	needle = NULL;
	needle = ft_strrchr(path, '/') + 1;
	if (path == NULL || *path == '\0')
		termination_with_error("There is wrong core name\n");
	if (needle == NULL)
		needle = path;
	ft_strcpy(core_name, needle);
	ft_putstr(needle);
}

void			process_n_flag(t_corewar **vm, char **arg_array)
{
	int8_t	number;
	char	*cur_str;

	cur_str = *arg_array;
	if (ft_isdigit(*cur_str) == false)
		termination_with_error("There is no value for -n flag\n");
	number = ft_atoi(cur_str);
	if (number < 1 || number > 4)
		termination_with_error("Wrong -n value\n");
	if (!((*vm)->cores[number] = (t_core*)ft_memalloc(sizeof(t_core))))
		termination_with_perror("Couldn't allocate memory for core\n", ENOMEM);
	init_core((*vm)->cores[number]);
	(*vm)->cores[number]->id = number;
	cur_str = *(arg_array++);
	if (cur_str && *cur_str != '\0' && ft_strlen(cur_str) > 4)
	{
		if (ft_strcmp(&((cur_str)[ft_strlen(cur_str) - 4]), ".cor") != 0)
			termination_with_error("There is wrong core name with -n flag\n");
	}
	else
		termination_with_error("There is wrong core name with -n flag\n");
	ft_strcpy((*vm)->cores[number]->file_path, cur_str);
}

void			parse_players(t_corewar **vm, char ***arg_array)
{
	uint8_t		number;
	
	if (ft_strcmp(**arg_array, "-n") == 0)
	{
		(*arg_array)++;
		process_n_flag(vm, *arg_array);
		(*arg_array) += 2;
	}
	else
	{
		number = get_core_number((*vm)->cores);
		if (!((*vm)->cores[number] = (t_core*)ft_memalloc(sizeof(t_core))))
			termination_with_perror("Couldn't allocate memory for core\n", ENOMEM);
		ft_strcpy((*vm)->cores[number]->file_path, **arg_array);
		(*vm)->cores[number]->id = number + 1;
		(*arg_array)++;
	}
	(*vm)->number_of_players++;
}

void			parse_arguments(t_corewar **vm, int argc, char *argv[])
{
	char		*arg_str;
	char		**arg_array;
	char		**cur_array;

	arg_str = concat_args(argv, argc);
	arg_array = ft_strsplit(arg_str, ' ');
	free(arg_str);
	cur_array = arg_array;
	while (cur_array - arg_array < argc)
	{
		if (ft_strcmp(*cur_array, "-dump") == 0)
			process_dump_flag(vm, *(cur_array + 1));
		else if (ft_strcmp(*cur_array, "-v") == 0)
			(*vm)->visual = true;
		else if (ft_strcmp(*cur_array, "-n") == 0 ||
			ft_strcmp(&((*cur_array)[ft_strlen(*cur_array) - 4]), ".cor") == 0)
			parse_players(vm, &cur_array);
		else
			termination_with_error("Undefined arg\n");
		free(*cur_array);
		cur_array++;
	}
	free(arg_array);
	(*vm)->winner = (*vm)->cores[(*vm)->number_of_players - 1];
}

//проверить валидность игроков:
//номера идут подрят, номера не повторяются, номер после -n < 4