/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_press.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:55:03 by screight          #+#    #+#             */
/*   Updated: 2019/12/02 07:06:50 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void    handle_speed(t_corewar *vm)
{
    if (vm->sdl->e->key.keysym.sym == SDLK_DOWN)
    {
        vm->sdl->delay += 20;
		stringColor(vm->sdl->ren, X, 800, "(DOWN)", SALM);
    }
    else
    {
        vm->sdl->delay -= 20;
		stringColor(vm->sdl->ren, X, 770, "(UP)", SALM);
    }
	SDL_RenderPresent(vm->sdl->ren);
	SDL_Delay(30);
}

void    handle_music(t_corewar *vm)
{
    if (vm->sdl->e->key.keysym.sym == SDLK_9)
    {
        if (Mix_PlayingMusic() == 0)
	    	Mix_PlayMusic(vm->sdl->music, -1);
	    else
	    	Mix_PausedMusic() == 1 ? Mix_ResumeMusic() : Mix_PauseMusic(); 
	    vm->sdl->mus = (vm->sdl->mus ? false : true);
    }
    else if (vm->sdl->e->key.keysym.sym == SDLK_0)
		vm->sdl->sound = (vm->sdl->sound) ? false : true;
    else
    {
        stringColor(vm->sdl->ren, X, 740, "(M)", SALM);
	    vm->sdl->sound = false;
	    SDL_RenderPresent(vm->sdl->ren);
	    if (vm->sdl->mus == true)
	    {
	    	Mix_HaltMusic();
	    	vm->sdl->mus = false;
	    }
	    SDL_Delay(40);
    }
}

bool    handle_pause(t_corewar *vm, bool *trig, bool pause)
{
	if (!pause)
	{
		stringColor(vm->sdl->ren, X, 650, "(SPACE)", SALM);
		SDL_RenderPresent(vm->sdl->ren);
		pause = true;
		while (pause)
			pause = handle_key_press(vm, trig, pause);
	}
	else
		pause = false;
	return (pause);
}

bool handle_key_press(t_corewar *vm, bool *trig, bool pause)
{
	while (SDL_PollEvent(vm->sdl->e) != 0)
	{
		if (vm->sdl->e->type == SDL_QUIT ||
			(vm->sdl->e->type == SDL_KEYDOWN) &&
    	        vm->sdl->e->key.keysym.sym == SDLK_ESCAPE)
			ft_close_sdl(vm->sdl);
		else if (vm->sdl->e->type == SDL_KEYDOWN && 
    	            (vm->sdl->e->key.keysym.sym == SDLK_RETURN ||
						vm->sdl->e->key.keysym.sym == SDLK_KP_ENTER) && trig)
			*trig = true;
		else if (vm->sdl->e->type == SDL_KEYDOWN &&
    	            vm->sdl->e->key.keysym.sym == SDLK_SPACE)
			pause = handle_pause(vm, trig, pause);
		else if (vm->sdl->e->type == SDL_KEYDOWN && 
    	            (vm->sdl->e->key.keysym.sym == SDLK_9 ||
    	                vm->sdl->e->key.keysym.sym == SDLK_m ||
    	                    vm->sdl->e->key.keysym.sym == SDLK_0))
			handle_music(vm);
		else if (vm->sdl->e->type == SDL_KEYDOWN && 
    	((vm->sdl->e->key.keysym.sym == SDLK_DOWN && vm->sdl->delay <= 40) ||
    		(vm->sdl->e->key.keysym.sym == SDLK_UP && vm->sdl->delay >= 20)))
    	    handle_speed(vm);
	}
	return (pause);
}