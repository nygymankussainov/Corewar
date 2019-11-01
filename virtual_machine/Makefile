# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egiant <egiant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 17:56:58 by hfrankly          #+#    #+#              #
#    Updated: 2019/11/01 16:31:51 by egiant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARCHIVE = corewar.a

NAME = corewar

LIB = ../libft/ft_printf
LIB_A = ../libft/libft.a $(LIB)/libftprintf.a

INCLUDES = -I ./includes  -I ../includes -I $(LIB) -I ../libft

LIBS = -L ../libft -lft -L ../libft/ft_printf -lftprintf

SRCDIR = src
OBJDIR = obj

SOURCES =	main.c \
			initialization.c \
			parse_arguments.c \
			exit.c \
			read_byte_code.c \


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
	@gcc $(CCFL) -o $(NAME) $(ARCHIVE) $(LIB_A)
	@echo "$(LOG_GREEN)Corewar has compiled successfully!$(LOG_NOCOLOR)"

clean:
	@make clean -sC $(LIB)
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(ARCHIVE)
	@/bin/rm -f $(NAME)
	@make fclean -sC $(LIB)

re: fclean all

.PHONY: all clean fclean re library obj_dir