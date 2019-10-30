# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: screight <screight@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/15 20:49:37 by screight          #+#    #+#              #
#    Updated: 2019/10/17 14:26:16 by screight         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re all

NAME	= libftprintf.a

LIBNAME = libft.a

SRC = ft_printf.c ft_get_flags.c ft_valid_flags.c ft_count_valid.c \
ft_edit_flags.c ft_get_width.c ft_get_precision.c ft_ignored_zero.c\
ft_ignored_space.c ft_get_type_size.c ft_get_type.c ft_solve_d.c \
ft_write_d_case1.c ft_write_d_case2.c ft_write_d_case3.c ft_solve_ox.c \
ft_write_ox_case1.c ft_write_ox_case2.c ft_write_ox_case3.c ft_solve_c.c \
ft_solve_s.c ft_write_utf.c ft_solve_p.c ft_valid_flags_c_s_p.c \
ft_solve_percent.c ft_solve_u.c ft_write_u_case1.c ft_write_u_case2.c \
ft_bigc_width.c ft_solve_f.c ft_write_f.c ft_get_binary.c \
ft_fract_to_dec_f.c ft_handle_binary_f.c ft_handle_output_f.c \
ft_handle_special_f.c ft_ints_to_dec_f.c ft_handle_doubles.c

LIBDIR 	= libft/

HEADER = headers/

LIBHEADER = libft/headers

SRCDIR	= sources/

OBJDIR	= objectives/

SRCS	= $(addprefix $(SRCDIR), $(SRC))

OBJS 	= $(addprefix $(OBJDIR), $(SRC:.c=.o))

CC		= -gcc

FLAGS 	= -Wall -Wextra -Werror

all: 		$(NAME)

$(NAME): 	$(OBJS) | mklib
			@cp $(LIBDIR)$(LIBNAME) .
			@mv $(LIBNAME) $(NAME)
			@ar rc $(NAME) $(OBJS)
			@ranlib $(NAME)

$(OBJS): 	$(OBJDIR)%.o: $(SRCDIR)%.c
			@mkdir -p $(OBJDIR)
			@$(CC) $(FLAGS)  -I $(HEADER) -I $(LIBHEADER) -c $< -o $@

mklib: 
			@make -C $(LIBDIR) --no-print-directory

clean:
			@/bin/rm -f $(OBJS)
			@rm -rf $(OBJDIR)
			@make clean -C $(LIBDIR) --no-print-directory

fclean: 	clean
			@/bin/rm -f $(NAME)
			@make fclean -C $(LIBDIR) --no-print-directory

re: 		fclean all
