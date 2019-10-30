# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 12:58:50 by vhazelnu          #+#    #+#              #
#    Updated: 2019/10/23 16:16:53 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[32m

NAME = libft.a

INCLUDES = -I ./

SRCDIR = src
OBJDIR = obj

SRCS = ft_memmove.c ft_strcmp.c ft_strncpy.c ft_itoa.c ft_memset.c ft_strcpy.c ft_strndup.c \
	  ft_atoi.c ft_lstadd.c ft_putchar.c ft_strdel.c ft_strnequ.c ft_bzero.c ft_lstdel.c ft_putchar_fd.c ft_strdup.c \
	  ft_strnew.c ft_lstdelone.c ft_putendl.c ft_strequ.c ft_strnlen.c ft_lstiter.c ft_strsplit.c \
	  ft_putendl_fd.c ft_striter.c ft_strnstr.c ft_isalnum.c ft_lstmap.c ft_putnbr.c ft_striteri.c ft_strrchr.c \
	  ft_isalpha.c ft_lstnew.c ft_putnbr_fd.c ft_strjoin.c ft_isascii.c ft_memalloc.c \
	  ft_strlcat.c ft_strstr.c ft_isdigit.c ft_memccpy.c ft_putstr_fd.c ft_strlen.c ft_strsub.c ft_islower.c ft_memchr.c \
	  ft_range.c ft_strmap.c ft_strtrim.c ft_isprint.c ft_memcmp.c ft_strcat.c ft_strmapi.c ft_tolower.c ft_isupper.c \
	  ft_memcpy.c ft_strchr.c ft_strncat.c ft_toupper.c ft_memdel.c ft_strclr.c ft_strncmp.c get_next_line.c ft_is_negative.c \
	  ft_sqrt.c ft_iterative_factorial.c ft_iterative_power.c ft_uitoa_base.c ft_itoa_base.c ft_atoi_base.c ft_power.c ft_swap.c \
	  ft_swap_str.c ft_power_db.c ft_putstr.c ft_realloc.c ft_bzero_null.c ft_skip_whitesp.c ft_revstr.c ft_itoa_ll.c iswhitesp.c \
	  ft_istabspace_in_str.c ft_free_two_dim_arr.c

SRC = $(addprefix $(SRCDIR)/, $(SRCS))

OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

CCFL = -Wall -Wextra -Werror

all: obj_dir $(NAME)

obj_dir:
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@echo "$(LOG_GREEN)Libft has compiled successfully!$(LOG_NOCOLOR)"
	@ranlib $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@gcc $(CCFL) -o $@ -c $< $(INCLUDES)

.PHONY: clean fclean re obj_dir

clean:
	@/bin/rm -rf $(OBJDIR)

fclean:	clean
	@/bin/rm -f $(NAME)

re:	fclean all
