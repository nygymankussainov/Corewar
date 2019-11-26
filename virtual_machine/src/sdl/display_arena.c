/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_arena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:36:16 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/26 03:41:59 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		set_player_color(t_corewar *vm, int i)
{
	if (i == 0)
		vm->cores[i]->color = 0xff5720b0;
	else if (i == 1)
		vm->cores[i]->color = 0xffb07620;
	else if (i == 2)
		vm->cores[i]->color = 0xff6fb020;
	else
		vm->cores[i]->color = 0xff20aeb0;
}

void display_player_data(t_corewar *vm)
{
	short	i;
	short	height;
	int		ll;

	ll = 0;
	t_carriage	*tmp;
	height = 300;
	i = -1;
	while (++i < vm->number_of_players)
	{
		ll = 0;
		tmp = vm->start_carriage;
		stringColor(vm->sdl->ren, SIZEX - 400, height, "player  :", vm->cores[i]->color);
		stringColor(vm->sdl->ren, SIZEX - 345, height, ft_itoa(i + 1), vm->cores[i]->color);
		stringColor(vm->sdl->ren, SIZEX - 320, height, vm->cores[i]->name, vm->cores[i]->color);
		stringColor(vm->sdl->ren, SIZEX - 400, height + 20, "last live:", 0xff000000); //0xffadadad
		while (tmp && ll <= 0)
		{
			if (tmp->id == i)
				ll = tmp->cycle_was_live;
			tmp = tmp->next;
		}
		stringColor(vm->sdl->ren, SIZEX - 310, height + 20, ft_itoa(ll), 0xff000000);
		stringColor(vm->sdl->ren, SIZEX - 400, height + 40, "lives in current period:", 0xff000000);
		stringColor(vm->sdl->ren, SIZEX - 200, height + 40, "xxxx", 0xff000000);
		height += 80;
	}
}

void		display_war_arena(t_corewar *vm, int raw, int col)
{
	int				i;
	int				border;
	static bool		start = true;
	t_carriage		*tmp;

	tmp = vm->start_carriage;
	while (tmp)
	{
		vm->vis_arena[tmp->position].outer_color = tmp->color + 45;
		vm->vis_arena[tmp->position].is_new = true;
		tmp = tmp->next;
	}
	i = -1;
	border = 0;
	while (++i < 4096)
	{
		if (i == border)
		{
			col = 12;
			raw = raw + RY + 1;
			border += 64;
		}
		if (vm->arena[i].color != 0x000000 && vm->arena[i].color != 0xff0000)
			(vm->vis_arena[i]).inner_color = vm->arena[i].color; //0xff42424;
		else
			(vm->vis_arena[i]).inner_color = 0xff424242;
		if (!(vm->vis_arena[i]).is_new)
			(vm->vis_arena[i]).outer_color = 0xff000000;
		vm->vis_arena[i].is_new = false;
		rectangleColor(vm->sdl->ren, col, raw, col + RX + 1, raw + RY + 1, vm->vis_arena[i].outer_color);
		rectangleColor(vm->sdl->ren, col + 1, raw + 1, col + RX, raw + RY, vm->vis_arena[i].outer_color);
		boxColor(vm->sdl->ren, col + 2, raw + 2, col + RX - 2 , raw + RY - 2, vm->vis_arena[i].inner_color);
		if (vm->vis_arena[i].light_count > 0)
			vm->vis_arena[i].light_count--;
		col += RX + 1;
	}
}

void		display_arena_state(t_corewar *vm)
{
	static bool start = true;
	int	x;
	int	y;
	int	xt;
	
	xt = 270;
	x = 400;
	y = 110;
//	SDL_Delay(20);//
	SDL_SetRenderDrawColor(vm->sdl->ren, 0x42, 0x42, 0x42, 0);
	SDL_RenderClear(vm->sdl->ren);
	boxColor(vm->sdl->ren, 10, 10, SIZEX - 435, SIZEY - 11, 0xff000000);
	boxColor(vm->sdl->ren, SIZEX - x, 10, SIZEX - 40, 60, 0xff698234);
	boxColor(vm->sdl->ren, SIZEX - x + 2, 12, SIZEX - 40 - 2, 60  - 2, 0xff424242);
	stringColor(vm->sdl->ren, SIZEX - 270, 32, "*#CORE_WAR#*", 0xff698234);
	if (start)
		stringColor(vm->sdl->ren, SIZEX - 305, 80, "Press <SPACE> to start", 0xff82369c);
	stringColor(vm->sdl->ren, SIZEX - x, y, "total cycles:", 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - xt, y, ft_itoa(vm->total_cycles), 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - x, y + 25, "current cycle:", 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - xt, y + 25, ft_itoa(vm->current_cycles), 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - x, y + 50, "cycles to die:", 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - xt, y + 50, ft_itoa(vm->cycles_to_die), 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - x, y + 75, "cycle delta:", 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - xt, y + 75, "50", 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - x, y + 100, "live number:         / 21", 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - xt, y + 100, ft_itoa(vm->live_count), 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - x, y + 125, "check number:        / 10", 0xff000000);
	stringColor(vm->sdl->ren, SIZEX - xt, y + 125, ft_itoa(vm->check_count), 0xff000000);
	thickLineColor(vm->sdl->ren, SIZEX - x, y + 160, SIZEX - 40, y + 160, 2, 0xff698234);
	display_player_data(vm);
	display_war_arena(vm, -2, 0);
	boxColor(vm->sdl->ren, SIZEX - x, 625, SIZEX - 40, 675, 0xff698234);
	boxColor(vm->sdl->ren, SIZEX - x + 2, 625 + 2, SIZEX - 290, 675 - 2, 0xff424242);
	boxColor(vm->sdl->ren, SIZEX - 287, 625 + 2, SIZEX - 40 - 2, 675 - 2, 0xff424242);
	stringColor(vm->sdl->ren, SIZEX - x + 15, 647, "THE WINNER", 0xff698234);
	if (vm->winner && vm->winner->name && !vm->start_carriage)
		stringColor(vm->sdl->ren, SIZEX - 270, 647, vm->winner->name, vm->winner->color);
	SDL_RenderPresent(vm->sdl->ren);
	while (start)
	{
		while (SDL_PollEvent(vm->sdl->e) != 0)
		{
			if ((vm->sdl->e->type == SDL_KEYDOWN && vm->sdl->e->key.keysym.sym == SDLK_SPACE))
				start = false;
		}
	}
}
