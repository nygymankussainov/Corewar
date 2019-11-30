# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/11/30 13:22:43 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[32m

ASMDIR = Assembler
VMDIR = vm
LIB = libft/ft_printf

.PHONY: all clean fclean re asm vm library

all: library asm vm
	@echo "$(LOG_GREEN)Corewar has compiled successfully!$(LOG_NOCOLOR)"

library:
	@make -sC $(LIB)

asm:
	@make -sC $(ASMDIR)

vm:
	@make -sC $(VMDIR)

clean:
	@make clean -sC $(LIB)
	@make clean -sC $(ASMDIR)
	@make clean -sC $(VMDIR)

fclean: clean
	@make fclean -sC $(LIB)
	@make fclean -sC $(ASMDIR)
	@make fclean -sC $(VMDIR)

re: fclean all
