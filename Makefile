# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/11/29 14:27:56 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASMDIR = Assembler
VMDIR = vm

.PHONY: all clean fclean re asm vm library

all: asm vm

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
