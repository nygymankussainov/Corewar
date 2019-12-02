/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:06:28 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/02 05:55:41 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# define SZX 1600
# define SZY 920
# define RX (SZX - 510) / 64
# define RY (SZY - 20 - 64) / 64
# define X 1200
# define Y 110
# define XT 1340
# define BLACK 0xff1c1c1c
# define GREY 0xff424242
# define RED 0xff5720b0
# define BLUE 0xffb07620
# define GREEN 0xff6fb020
# define YELLOW 0xff20aeb0
# define WHITE 0x65ffffff
# define GCOL 0xff698234
# define DIM 0x50000000
# define SALM 0xff5867a6
//#include "SDL.h"
//#include "SDL2_gfxPrimitives.h"
//#include "SDL_mixer.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL_mixer.h"

typedef struct s_sdl t_sdl;

struct s_sdl
{
	SDL_Window *win;
	SDL_Surface *sfc;
	SDL_Renderer *ren;
	SDL_Event *e;
	Mix_Music *music;
	Mix_Chunk *live;
	Mix_Chunk *dead_car;
	Mix_Chunk *copy_car;
	bool		sound;
	bool		mus;
	short		delay;
};

/*
** sdl_init
*/
t_sdl				*sdl_init(void);
void				ft_close_sdl(t_sdl *sdl);
void				vis_corewar(t_corewar *vm);
void				set_player_color(t_corewar *vm, int i);
void				handle_key_press(t_corewar *vm, bool *trig);
void				display_winner_vis(t_corewar *vm);
void				display_player_data(t_corewar *vm, short h, short i);
void				display_vm_state_vis(t_corewar *vm);
void				display_war_state(t_corewar *vm);
void				display_header(t_corewar *vm, bool start);

#endif