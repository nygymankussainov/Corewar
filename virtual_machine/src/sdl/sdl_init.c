/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:03:45 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/17 13:33:49 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_sdl		*sdl_init(void)
{
	t_sdl		*sdl;

	if (!(sdl = (t_sdl*)malloc(sizeof(t_sdl))))
		termination_with_perror("Sdl init error", ENOMEM);
	sdl->win = NULL;
	sdl->sfc = NULL;
	sdl->e = NULL;
	if (!(sdl->e = (SDL_Event*)malloc(sizeof(SDL_Event))))
		termination_with_perror("Sdl init error", ENOMEM);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		termination_with_perror("Sdl init error", ENOMEM);
	else
	{
		SDL_CreateWindowAndRenderer(SIZEX, SIZEY, 0, &sdl->win, &sdl->ren);
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 < 0))
			termination_with_perror("Sdl init error", ENOMEM);
		if (sdl->win == NULL || sdl->ren == NULL)
			termination_with_perror("Sdl init error", ENOMEM);
		SDL_RenderClear(sdl->ren);
	}
	return (sdl);
}

void	ft_close_sdl(t_sdl *sdl)
{
	free(sdl->e);
	Mix_FreeMusic(sdl->music);
	SDL_DestroyWindow(sdl->win);
	SDL_DestroyRenderer(sdl->ren);
	Mix_Quit();
	SDL_Quit();
	free(sdl);
}
