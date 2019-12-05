# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/12/05 20:58:18 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = ../

INCLUDES = -I ../

SRCS = ft_symbol.c ft_printf.c ft_number.c ft_conv_f.c ft_conv_x.c ft_conv_d.c ft_conv_p.c ft_conv_o.c ft_conv_u.c width_for_f.c ft_conv_b.c \
		longadd.c longmulti.c decimal_part.c longdiv.c integer_part.c rounding_and_print.c calculate_decimal.c width.c find_conv_or_whitesp.c \

OBJ = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
OBJDIR = obj

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re obj_dir library

all: obj_dir $(NAME)

obj_dir:
	@mkdir -p $(OBJDIR)

library:
	@make -sC $(LIBFT)

$(NAME): library $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJDIR)/%.o: %.c
	@gcc $(CCFL) -o $@ -c $< $(INCLUDES)

clean:
	@make clean -C $(LIBFT)
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C $(LIBFT)
	@/bin/rm -f $(NAME)

re: fclean all
