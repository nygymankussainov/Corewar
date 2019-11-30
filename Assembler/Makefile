# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/11/30 13:28:20 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[32m

NAME = asm

LIB = ../libft/ft_printf
LIB_A = ../libft/libft.a $(LIB)/libftprintf.a

INCLUDES = -I ../includes  -I ../ -I $(LIB) -I ../libft

SOURCES = asm.c print_error.c tokenization.c create_token.c check_line.c write_label_in_token.c print_token.c compile_into_bytecode.c \
			validate_file.c validation.c validate_name_and_comment.c create_operation.c validate_number.c validate_args.c check_quotes.c \
			validate_tokens.c validate_labels.c ft_itoh.c free_structs.c \

SRCDIR = src
OBJDIR = obj

SRC = $(addprefix $(SRCDIR)/, $(SOURCES))

OBJ = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re obj_dir debug

all: obj_dir $(NAME)

debug: all
	@gcc $(CCFL) -o $(NAME) $(SRC) $(LIB_A) $(INCLUDES) -g

obj_dir:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@gcc $(CCFL) -o $@ -c $< $(INCLUDES)

$(NAME): $(OBJ)
	@gcc $(CCFL) -o $(NAME) $(OBJ) $(LIB_A)
	@echo "$(LOG_GREEN)Asm has compiled successfully!$(LOG_NOCOLOR)"

clean:
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
