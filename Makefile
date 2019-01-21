# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gscolera <gscolera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/13 17:05:45 by gscolera          #+#    #+#              #
#    Updated: 2019/01/21 16:40:49 by gscolera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRC = ft_ls.c src/*.c
INC = -Iincludes/
FLAGS = -Wall -Werror -Wextra -Ofast

$(NAME):
	make re -C ft_printf
	gcc $(FLAGS) $(SRC) $(INC) -L./ft_printf -lftprintf -o $(NAME)
	make clean -C ft_printf

all: $(NAME)

clean:
	/bin/rm -f *.o
fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C ft_printf
re: fclean all
