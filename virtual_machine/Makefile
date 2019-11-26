# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: screight <screight@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 17:56:58 by hfrankly          #+#    #+#              #
#    Updated: 2019/11/19 23:28:31 by screight         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[32m

ARCHIVE = corewar.a

NAME = corewar

SDL = -lSDL2_gfx -lSDL2_mixer -lSDL2_ttf -lSDL2

LIB = ../libftprintf
LIB_A = $(LIB)/libftprintf.a

INCLUDES = -I ./includes  -I ../includes -I $(LIB) -I ../libftprintf/headers -I ../libftprintf/libft/headers

LIBS = -L ../libftprintf -lftprintf

SRCDIR = src
OBJDIR = obj

SOURCES =	main.c \
			initialization/initialization.c \
			initialization/set_params.c\
			parsing/parse_arguments.c \
			validation/read_byte_code.c \
			sdl/sdl_init.c \
			sdl/display_arena.c \
			war/start_war.c \
			war/operations.c \
			war/check.c \
			war/carriage_execution.c \
			war/carriage_interaction.c \
			war/execute_op.c \
			exit.c \


SRC = $(addprefix $(SRCDIR)/, $(SOURCES))

OBJ = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

CCFL = -g

all: obj_dir library $(ARCHIVE) $(NAME)

obj_dir:
	@mkdir -p $(OBJDIR)

library:
	@make -sC $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@gcc $(CCFL) -o $@ -c $< $(INCLUDES)

$(ARCHIVE): $(OBJ)
	@ar rc $(ARCHIVE) $(OBJ)
	@ranlib $(ARCHIVE)

$(NAME): $(OBJ)
	@gcc $(CCFL) -o $(NAME) $(ARCHIVE) $(LIB_A) $(SDL)
	@echo "$(LOG_GREEN)Corewar has compiled successfully!$(LOG_NOCOLOR)"

clean:
	@make clean -sC $(LIB)

fclean: clean
	@/bin/rm -f $(ARCHIVE)
	@/bin/rm -f $(NAME)
	@make fclean -sC $(LIB)

re: fclean all

.PHONY: all clean fclean re library obj_dir