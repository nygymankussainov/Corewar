# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egiant <egiant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/26 21:15:02 by egiant            #+#    #+#              #
#    Updated: 2019/10/30 16:36:49 by egiant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all

NAME = vm

LIBPRDIR = libftprintf
LIBDIR = libftprintf/libft
FLAGS = -g
HEADER = -I headers/ -I $(LIBPRDIR)/headers -I $(LIBDIR)/headers

OBJ_DIR = objectives/
SRC_DIR = sources/

SRCS =	main.c initialization.c

OBJS 	= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) | mklibpr
	
	gcc $(FLAGS) $(OBJS) -L $(LIBPRDIR) -lftprintf $(HEADER) -o $(NAME)

$(OBJS) : $(OBJ_DIR)%.o: $(SRC_DIR)%.c
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