/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 00:53:14 by screight          #+#    #+#             */
/*   Updated: 2019/12/02 04:33:13 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"


void	display_header(t_corewar *vm, bool start)
{
	boxColor(vm->sdl->ren, 10, 10, SZX - 435, SZY - 11, BLACK);
	boxColor(vm->sdl->ren, X, 20, SZX - 40, 80, GCOL);
	boxColor(vm->sdl->ren, X + 2, 22, SZX - 42, 78, GREY);
	stringColor(vm->sdl->ren, SZX - 270, 44, "*#CORE_WAR#*", SALM);
	if (!start)
		stringColor(vm->sdl->ren, SZX - 310, SZY - 56, 
											"Press <ENTER> to start", SALM);
	else
	{
		boxColor(vm->sdl->ren, X, SZY - 80, SZX - 40, SZY - 20, GCOL);
		boxColor(vm->sdl->ren, X + 2, SZY - 78, SZX - 290, SZY - 22, GREY);
		boxColor(vm->sdl->ren, SZX - 287, SZY - 78, SZX - 42, SZY - 22, GREY);
		stringColor(vm->sdl->ren, X + 11, SZY - 56, "THE WINNER", SALM);
	}
}

void display_player_data(t_corewar *vm, short h, short i)
{
	int	n;
	t_carriage *tmp;
	
	while (++i < vm->number_of_players)
	{
		tmp = vm->start_carriage;
		stringColor(vm->sdl->ren, X, h, "player  :", vm->cores[i]->color);
		stringColor(vm->sdl->ren, 1260, h, ft_itoa(i + 1), vm->cores[i]->color);
		stringColor(vm->sdl->ren, 1290, h, vm->cores[i]->name,
														vm->cores[i]->color);
		stringColor(vm->sdl->ren, X, h + 20, "last live:", WHITE);
		stringColor(vm->sdl->ren, X, h + 40, "lives in current period:", WHITE);
		stringColor(vm->sdl->ren, 1425, h + 20,
								ft_itoa(vm->cores[i]->cycle_was_live), SALM);
		stringColor(vm->sdl->ren, 1425, h + 40,
								ft_itoa(vm->cores[i]->lives_in_period), SALM);
		if (vm->current_cycles == 0)
			vm->cores[i]->lives_in_period = 0;
		h += 80;
	}
}

void	display_vm_state_vis(t_corewar *vm)
{
	thickLineColor(vm->sdl->ren, X, 620, SZX - 40, 620, 2, GCOL);
    stringColor(vm->sdl->ren, X, 650, "(SPACE)", GCOL);
	stringColor(vm->sdl->ren, SZX - 330, 650, "- pause corewar", WHITE);
	stringColor(vm->sdl->ren, X, 680, "(9)", (vm->sdl->mus ? SALM : GCOL));
	stringColor(vm->sdl->ren, SZX - 330, 680, "- play / pause music", WHITE);
    stringColor(vm->sdl->ren, X, 710, "(0)", (vm->sdl->sound ? SALM : GCOL));
	stringColor(vm->sdl->ren, SZX - 330, 710, "- on / off sounds", WHITE);
	stringColor(vm->sdl->ren, X, 740, "(M)", GCOL);
	stringColor(vm->sdl->ren, SZX - 330, 740, "- mute", WHITE);
	stringColor(vm->sdl->ren, X, 770, "(UP)", GCOL);
	stringColor(vm->sdl->ren, SZX - 330, 770, "- speed up", WHITE);
	stringColor(vm->sdl->ren, X, 800, "(DOWN)", GCOL);
	stringColor(vm->sdl->ren, SZX - 330, 800, "- speed down", WHITE);
	stringColor(vm->sdl->ren, SZX - 180, 800, "CURRENT SPEED:", WHITE);
	stringColor(vm->sdl->ren, SZX - 48, 800,
										ft_itoa(3 - vm->sdl->delay / 20), SALM);
	stringColor(vm->sdl->ren, SZX - 180, 770, "CARRIAGES NUM:", WHITE);
	stringColor(vm->sdl->ren, SZX - 48, 770, ft_itoa(vm->carriage_count), SALM);
}

void display_war_state(t_corewar *vm)
{
	stringColor(vm->sdl->ren, X, Y, "total cycles:", WHITE);
	stringColor(vm->sdl->ren, X, Y + 25, "current cycle:", WHITE);
	stringColor(vm->sdl->ren, X, Y + 50, "cycles to die:", WHITE);
	stringColor(vm->sdl->ren, X, Y + 75, "cycle delta:", WHITE);
	stringColor(vm->sdl->ren, X, Y + 100, "live number:", WHITE);
	stringColor(vm->sdl->ren, X, Y + 125, "check number:", WHITE);
	stringColor(vm->sdl->ren, XT, Y, ft_itoa(vm->total_cycles), SALM);
	stringColor(vm->sdl->ren, XT, Y + 25, ft_itoa(vm->current_cycles), SALM);
	stringColor(vm->sdl->ren, XT, Y + 50, ft_itoa(vm->cycles_to_die), SALM);
	stringColor(vm->sdl->ren, XT, Y + 75, "50", SALM);
	stringColor(vm->sdl->ren, SZX - 220, Y + 100, "/ 21", SALM);
	stringColor(vm->sdl->ren, XT, Y + 100, ft_itoa(vm->live_count), SALM);
	stringColor(vm->sdl->ren, SZX - 220, Y + 125, "/ 10", SALM);
	stringColor(vm->sdl->ren, XT, Y + 125, ft_itoa(vm->check_count), SALM);
	thickLineColor(vm->sdl->ren, X, Y + 165, SZX - 40, Y + 165, 2, GCOL);
}