# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/12/05 21:00:09 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG_NOCOLOR = \033[0m
LOG_GREEN = \033[1;32m

ASMDIR = assembler
VMDIR = virtual_machine

.PHONY: all clean fclean re asm vm library

all: library vm asm
	@echo "$(LOG_GREEN)Corewar has been compiled!$(LOG_NOCOLOR)"

asm:
	@make -sC $(ASMDIR)

vm:
	@make -sC $(VMDIR)

clean:
	@make clean -sC $(ASMDIR)
	@make clean -sC $(VMDIR)

fclean: clean
	@make fclean -sC $(ASMDIR)
	@make fclean -sC $(VMDIR)

re: fclean all
