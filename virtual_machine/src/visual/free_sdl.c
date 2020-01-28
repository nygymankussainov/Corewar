/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:52:06 by screight          #+#    #+#             */
/*   Updated: 2019/12/05 20:21:55 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	annonce_winner_vis(t_corewar *vm)
{
	vis_corewar(vm);
	stringColor(vm->sdl->ren, SZX - 250, SZY - 56,
									vm->winner->name, vm->winner->color);
	SDL_RenderPresent(vm->sdl->ren);
}

void	free_sdl(t_sdl *sdl)
{
	if (sdl)
	{
		if (sdl->e)
			free(sdl->e);
		if (sdl->music)
			Mix_FreeMusic(sdl->music);
		if (sdl->live)
			Mix_FreeChunk(sdl->live);
		if (sdl->dead_car)
			Mix_FreeChunk(sdl->dead_car);
		if (sdl->copy_car)
			Mix_FreeChunk(sdl->copy_car);
		SDL_DestroyWindow(sdl->win);
		SDL_DestroyRenderer(sdl->ren);
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		free(sdl);
	}
}
