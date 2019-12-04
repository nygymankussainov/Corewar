# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 17:56:58 by hfrankly          #+#    #+#              #
#    Updated: 2019/12/04 18:43:51 by hfrankly         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[1;32m
LOG_RED = \033[31m
LOG_BLUE = \033[1;34m
NAME = corewar

SDL = -L ~/.brew/Cellar/sdl2/2.0.10/lib -l SDL2-2.0.0 \
		`sdl2-config --libs` -lSDL2_gfx -lSDL2_mixer -lSDL2_ttf -lm
LIBPRDIR = ../libftprintf
LIBDIR = ../libftprintf/libft
FLAGS = -g
HEADER = -I ../includes/ -I includes/ -I $(LIBPRDIR)/headers -I $(LIBDIR)/headers \
-I./includes/sdl/SDL2 -I./includes/sdl/SDL2_GFX -I./includes/sdl/SDL2_MIX `sdl2-config --cflags`

OBJ_DIR = obj/
SRC_DIR = src/
FREE_DIR = src/free/
INIT_DIR = src/initialization/
PARSING_DIR = src/parsing/
VALID_DIR = src/validation/
OPER_DIR = src/operations/
WAR_DIR = src/war/
VIS_DIR = src/visual/

SRC =	    main.c \
			exit.c
FREE_SRC = free_corewar.c
INIT_SRC = initialization.c \
            set_params.c
PARSING_SRC = parse_arguments.c
VALID_SRC = read_byte_code.c
WAR_SRC = 	start_war.c \
          	operations.c \
          	check.c \
          	carriage_execution.c \
          	carriage_interaction.c \
          	execute_op.c
VIS_SRC	=	vis_corewar.c \
			display_data.c \
			sdl_init.c \
			handle_key_press.c

MAIN_OBJS 	= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
FREE_OBJS 	= $(addprefix $(OBJ_DIR), $(FREE_SRC:.c=.o))
INIT_OBJS 	= $(addprefix $(OBJ_DIR), $(INIT_SRC:.c=.o))
PARSING_OBJS = $(addprefix $(OBJ_DIR), $(PARSING_SRC:.c=.o))
VALID_OBJS 	= $(addprefix $(OBJ_DIR), $(VALID_SRC:.c=.o))
WAR_OBJS 	= $(addprefix $(OBJ_DIR), $(WAR_SRC:.c=.o))
VIS_OBJS	= $(addprefix $(OBJ_DIR), $(VIS_SRC:.c=.o))

all: cmpl $(NAME)

$(NAME): $(MAIN_OBJS) $(FREE_OBJS) $(INIT_OBJS) $(PARSING_OBJS) $(VALID_OBJS) $(WAR_OBJS) $(VIS_OBJS)| mklibpr
	@gcc $(FLAGS) $(MAIN_OBJS) $(FREE_OBJS) $(INIT_OBJS) $(PARSING_OBJS) $(VALID_OBJS) $(WAR_OBJS) $(VIS_OBJS) -L $(LIBPRDIR) -lftprintf $(HEADER) -o $(NAME) $(SDL)
	@echo "$(LOG_GREEN)Corewar has been compiled!$(LOG_NOCOLOR)"
		
$(MAIN_OBJS) :	$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(FREE_OBJS) :	$(OBJ_DIR)%.o: $(FREE_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(INIT_OBJS) :	$(OBJ_DIR)%.o: $(INIT_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(PARSING_OBJS) :	$(OBJ_DIR)%.o: $(PARSING_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(VALID_OBJS) :	$(OBJ_DIR)%.o: $(VALID_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(WAR_OBJS) :	$(OBJ_DIR)%.o: $(WAR_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(VIS_OBJS) :	$(OBJ_DIR)%.o: $(VIS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@ $(HEADER)

cmpl:
		@echo "$(LOG_BLUE).:!COMPILING!:.$(LOG_NOCOLOR)"

mklibpr:
		@make -C $(LIBPRDIR) --no-print-directory

clean:
			@/bin/rm -f $(OBJS)
			@rm -rf $(OBJ_DIR)
			@make clean -C $(LIBPRDIR) --no-print-directory
			@echo "$(LOG_RED)Object files have been cleaned.$(LOG_NOCOLOR)"

fclean: 	clean
			@/bin/rm -f $(NAME)
			@make fclean -C $(LIBPRDIR) --no-print-directory
			@echo "$(LOG_RED)Corewar have been deleted.$(LOG_NOCOLOR)"
re: 		fclean all