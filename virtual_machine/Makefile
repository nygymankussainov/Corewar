# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 17:56:58 by hfrankly          #+#    #+#              #
#    Updated: 2019/11/17 13:36:59 by hfrankly         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[32m

NAME = corewar

LIBPRDIR = ../libftprintf
LIBDIR = ../libftprintf/libft
FLAGS = -g
HEADER = -I ../includes/ -I includes/ -I $(LIBPRDIR)/headers -I $(LIBDIR)/headers

OBJ_DIR = obj/
SRC_DIR = src/
FREE_DIR = src/free/
INIT_DIR = src/initialization/
PARSING_DIR = src/parsing/
VALID_DIR = src/validation/
WAR_DIR = src/war/

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

MAIN_OBJS 	= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
FREE_OBJS 	= $(addprefix $(OBJ_DIR), $(FREE_SRC:.c=.o))
INIT_OBJS 	= $(addprefix $(OBJ_DIR), $(INIT_SRC:.c=.o))
PARSING_OBJS = $(addprefix $(OBJ_DIR), $(PARSING_SRC:.c=.o))
VALID_OBJS 	= $(addprefix $(OBJ_DIR), $(VALID_SRC:.c=.o))
WAR_OBJS 	= $(addprefix $(OBJ_DIR), $(WAR_SRC:.c=.o))

all: $(NAME)

$(NAME): $(MAIN_OBJS) $(FREE_OBJS) $(INIT_OBJS) $(PARSING_OBJS) $(VALID_OBJS) $(WAR_OBJS) | mklibpr
	gcc $(FLAGS) $(MAIN_OBJS) $(FREE_OBJS) $(INIT_OBJS) $(PARSING_OBJS) $(VALID_OBJS) $(WAR_OBJS) -L $(LIBPRDIR) -lftprintf $(HEADER) -o $(NAME)
	@echo "$(LOG_GREEN)Corewar has compiled successfully!$(LOG_NOCOLOR)"

$(MAIN_OBJS) :	$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(FREE_OBJS) :	$(OBJ_DIR)%.o: $(FREE_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(INIT_OBJS) :	$(OBJ_DIR)%.o: $(INIT_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(PARSING_OBJS) :	$(OBJ_DIR)%.o: $(PARSING_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(VALID_OBJS) :	$(OBJ_DIR)%.o: $(VALID_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) -c $< -o $@ $(HEADER)

$(WAR_OBJS) :	$(OBJ_DIR)%.o: $(WAR_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLAGS) -c $< -o $@ $(HEADER)

mklibpr:
		@make -C $(LIBPRDIR) --no-print-directory

clean:
			@/bin/rm -f $(OBJS)
			@rm -rf $(OBJ_DIR)
			@make clean -C $(LIBPRDIR) --no-print-directory

fclean: 	clean
			@/bin/rm -f $(NAME)
			@make fclean -C $(LIBPRDIR) --no-print-directory

re: 		fclean all