# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikadimi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/10 11:59:28 by ikadimi           #+#    #+#              #
#    Updated: 2019/03/10 14:44:27 by ikadimi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME2 = libft.a
SRC = main.c path_checker.c list_maker.c variable_and_lignes.c built_in.c helping_fonctions.c list_change.c read_line_plus.c
LIBSRC = libft/*.c
SRC2 = *.o

all: $(NAME)

$(NAME):
	@echo "building minishell ..."
	@gcc -Wall -Wextra -Werror -c $(LIBSRC)
	@ar rc $(NAME2) $(SRC2)
	@ranlib $(NAME2)
	@gcc -Wall -Wextra -Werror $(NAME2) $(SRC) -o $(NAME)
clean:
	@/bin/rm -f $(SRC2)
fclean: clean
	@echo "full cleaning"
	@/bin/rm -f $(NAME) $(NAME2)
re: fclean all
