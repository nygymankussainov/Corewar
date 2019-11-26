/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:06:28 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/26 17:17:05 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# define SIZEX 1600
# define SIZEY 920

#define RX (SIZEX - 510) / 64
#define RY (SIZEY - 20 - 64) / 64

#include "virtual_machine.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_mixer.h"

typedef struct s_sdl			t_sdl;
typedef struct s_vis_arena		t_vis_arena;

struct						s_sdl
{
	SDL_Window				*win;
	SDL_Surface				*sfc;
	SDL_Texture				*text;
	SDL_Renderer			*ren;
	SDL_Event				*e;
	Mix_Music				*music;
};

struct						s_vis_arena
{
	bool					is_new;
	int						light_count;
	int32_t					inner_color;
	int32_t					outer_color;
};
/*
** sdl_init
*/
t_sdl						*sdl_init(void);
void						ft_close_sdl(t_sdl *sdl);

/*
** display_arena
*/
void						display_arena_state(t_corewar *vm);
void						set_player_color(t_corewar *vm, int i); // **added by screight**

#endif