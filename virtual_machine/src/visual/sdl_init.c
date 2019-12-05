/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:48:27 by screight          #+#    #+#             */
/*   Updated: 2019/12/05 14:14:42 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		init_and_load_audio(t_sdl *sdl)
{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			ft_printf("Mix_OpenAudio: %s\n", Mix_GetError());
		if (!(sdl->music = Mix_LoadMUS("pacifica.ogg"))
				|| !(sdl->live = Mix_LoadWAV("live.wav"))	
					|| !(sdl->dead_car = Mix_LoadWAV("zoom.wav"))
						|| !(sdl->copy_car = Mix_LoadWAV("jump.wav")))
			ft_close_sdl(sdl);
}

void		load_font(t_sdl *sdl)
{
	char *myfont;
	FILE *file;

	myfont = NULL;
	if (!(myfont = (char *)malloc(sizeof(char) * 7680)))
		termination_with_perror("Sdl init error", ENOMEM);
	if (!(file = fopen("9x15B.fnt", "r")))
	{
		perror("Failed to open file");
		ft_close_sdl(sdl);
	}
	fread(myfont, 7680, 1, file);
	fclose(file);
	gfxPrimitivesSetFont(myfont, 9, 15);
	sdl->myfont = myfont;
}

void		sdl_var_init(t_sdl *sdl)
{
	sdl->win = NULL;
	sdl->sfc = NULL;
	sdl->e = NULL;
	sdl->ren = NULL;
	sdl->music = NULL;
	sdl->live = NULL;
	sdl->copy_car = NULL;
	sdl->dead_car = NULL;
	sdl->sound = false;
	sdl->mus = false;
	sdl->delay = 0;
}

t_sdl		*sdl_init(void)
{
	t_sdl	*sdl;

	if (!(sdl = (t_sdl*)malloc(sizeof(t_sdl))))
		termination_with_perror("Sdl init error", ENOMEM);
	sdl_var_init(sdl);
	if (!(sdl->e = (SDL_Event*)malloc(sizeof(SDL_Event))))
		termination_with_perror("Sdl init error", ENOMEM);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0)
		termination_with_perror("Sdl init error", ENOMEM);
	else
	{
		sdl->win = SDL_CreateWindow("CoreWar", SDL_WINDOWPOS_UNDEFINED, 
					SDL_WINDOW_ALWAYS_ON_TOP, SZX, SZY, SDL_WINDOW_SHOWN);
		sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
		if (sdl->win == NULL || sdl->ren == NULL)
				termination_with_perror("SDL init error", ENOMEM);
		init_and_load_audio(sdl);
		load_font(sdl);
		SDL_RenderClear(sdl->ren);
	}
	return (sdl);
}

void	ft_close_sdl(t_sdl *sdl)
{
	free(sdl->e);
	Mix_FreeMusic(sdl->music);
	Mix_FreeChunk(sdl->live);
	Mix_FreeChunk(sdl->dead_car);
	Mix_FreeChunk(sdl->copy_car);
	SDL_DestroyWindow(sdl->win);
	SDL_DestroyRenderer(sdl->ren);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	free(sdl);
	exit (0); //temporary
}
