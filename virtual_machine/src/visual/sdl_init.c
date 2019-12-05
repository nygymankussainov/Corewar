/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:48:27 by screight          #+#    #+#             */
/*   Updated: 2019/12/05 17:12:21 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int		load_audio(t_sdl *sdl)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (0);
	if (!(sdl->music = Mix_LoadMUS("pacifica.ogg"))
			|| !(sdl->live = Mix_LoadWAV("live.wav"))	
				|| !(sdl->dead_car = Mix_LoadWAV("zoom.wav"))
					|| !(sdl->copy_car = Mix_LoadWAV("jump.wav")))
		return(0);
	return (1);
}

int		load_font(t_sdl *sdl)
{
	char *myfont;
	FILE *file;

	myfont = NULL;
	if (!(myfont = (char *)malloc(sizeof(char) * 7680)))
		return (0);
	if (!(file = fopen("9x15B.fnt", "r")))
		return (0);
	fread(myfont, 7680, 1, file);
	fclose(file);
	gfxPrimitivesSetFont(myfont, 9, 15);
	sdl->myfont = myfont;
	return (1);
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

t_sdl		*sdl_init(t_corewar *vm)
{
	t_sdl	*sdl;

	if (!(sdl = (t_sdl*)malloc(sizeof(t_sdl))))
		close_vis(vm, NULL, ENOMEM, false);
	sdl_var_init(sdl);
	if (!(sdl->e = (SDL_Event*)malloc(sizeof(SDL_Event))))
		close_vis(vm, NULL, ENOMEM, false);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0)
		close_vis(vm, NULL, ENOMEM, false);
	else
	{
		sdl->win = SDL_CreateWindow("CoreWar", SDL_WINDOWPOS_CENTERED, 
					SDL_WINDOW_ALWAYS_ON_TOP, SZX, SZY, SDL_WINDOW_SHOWN);
		sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_SOFTWARE);
		if (sdl->win == NULL || sdl->ren == NULL)
			close_vis(vm, NULL, ENOMEM, false);
		if (!load_audio(sdl))
			close_vis(vm, NULL, -1, true);
		if (!load_font(sdl))
			close_vis(vm, "Bad font file", -1, false);
		SDL_RenderClear(sdl->ren);
	}
	return (sdl);
}

void	close_vis(t_corewar *vm, char *err, int code, bool mix)
{
	if (code >= 0)
	{
		errno = code;
		perror("SDL initializaton error");
	}
	else if (mix)
	{
		write(2, "Mix_Audio: %s\n", 11);
		write(2, Mix_GetError(), 20);
	}
	else if (err)
		write(2, err, ft_strlen(err));
	free_corewar(vm);
	exit(0);
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
