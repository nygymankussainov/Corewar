/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:06:28 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/17 13:45:34 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# define SIZEX 1600
# define SIZEY 900

#include "virtual_machine.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_mixer.h"

typedef struct s_sdl			t_sdl;

struct						s_sdl
{
	SDL_Window				*win;
	SDL_Surface				*sfc;
	SDL_Texture				*text;
	SDL_Renderer			*ren;
	SDL_Event				*e;
	Mix_Music				*music;
};

/*
** sdl_init
*/
t_sdl		*sdl_init(void);
void		ft_close_sdl(t_sdl *sdl);

/*
** display_arena
*/
void		display_arena_state(t_corewar *vm);

#endif