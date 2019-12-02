/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_corewar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:46:08 by screight          #+#    #+#             */
/*   Updated: 2019/12/02 05:49:39 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void set_player_color(t_corewar *vm, int i)
{
	if (i == 0)
		vm->cores[i]->color = RED;
	else if (i == 1)
		vm->cores[i]->color = BLUE;
	else if (i == 2)
		vm->cores[i]->color = GREEN;
	else
		vm->cores[i]->color = YELLOW;
	vm->cores[i]->cycle_was_live = 0;
	vm->cores[i]->lives_in_period = 0;
}

void		set_carriages_vis(t_corewar *vm)
{
	t_carriage *tmp;

	tmp = vm->start_carriage;
	while (tmp)
	{
		vm->arena[tmp->position].out_col = tmp->color + 45;
		vm->arena[tmp->position].touch = true;
		tmp = tmp->next;
	}
}

void	set_arena_colors_vis(t_corewar *vm, int raw, int col, short i)
{
	if (vm->arena[i].light_count > 0)
	{
		if (vm->arena[i].light_count == 1)
			vm->arena[i].color -= DIM;
		vm->arena[i].light_count--;
	}
	if (!(vm->arena[i]).touch)
		(vm->arena[i]).out_col = BLACK;
	vm->arena[i].touch = false;
	rectangleColor(vm->sdl->ren, col, raw, col + RX + 1, raw + RY + 1,
														vm->arena[i].out_col);
	rectangleColor(vm->sdl->ren, col + 1, raw + 1, col + RX, raw + RY,
														vm->arena[i].out_col);
	boxColor(vm->sdl->ren, col + 2, raw + 2, col + RX - 2, raw + RY - 2,
														vm->arena[i].color);
	if (vm->arena[i].live_count > 0)
	{
		boxColor(vm->sdl->ren, col + 3, raw + 3, col + RX - 3,
														raw + RY - 3, WHITE);
		vm->arena[i].live_count--;
	}
}

void display_arena_vis(t_corewar *vm, short i)
{
	short col;
	short raw;
	short border;

	raw = -2;
	border = 0;
	while (++i < 4096)
	{
		if (i == border)
		{
			col = 12;
			raw = raw + RY + 1;
			border += 64;
		}
		set_arena_colors_vis(vm, raw, col, i);
		col += RX + 1;
	}
}

void	vis_corewar(t_corewar *vm)
{
	static bool start = false;

	if (vm->sdl->delay)
		SDL_Delay(vm->sdl->delay);
	SDL_SetRenderDrawColor(vm->sdl->ren, 0x42, 0x42, 0x42, 0);
	SDL_RenderClear(vm->sdl->ren);
	display_header(vm, start);
	display_war_state(vm);
	display_player_data(vm, 300, -1);
	set_carriages_vis(vm);
	display_vm_state_vis(vm);
	display_arena_vis(vm, -1);
	SDL_RenderPresent(vm->sdl->ren);
	while (!start)
		handle_key_press(vm, &start);
}
