# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/28 14:03:26 by jtranchi          #+#    #+#              #
#    Updated: 2016/02/03 00:09:48 by jtranchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
LIB = libft/libft.a
SRC =	srcs/ls.c \
		srcs/errors.c \
		srcs/ls_l.c \
		srcs/options.c \
		srcs/openread.c \
		srcs/bonus.c \
		srcs/rights.c \
		srcs/opt.c
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra
CG = \033[92m
CY =  \033[93m
CE = \033[0m
CB = \033[34m

all: start $(NAME)

$(NAME): $(OBJ)
	@echo "$(CY)[FT_LS] :$(CE) $(CG)Creating Library$(CE)";
	-@make -C libft nohd
	@echo "$(CY)[FT_LS] :$(CE) $(CG)Compiling ft_ls ...$(CE)";
	@gcc -o $(NAME) $(FLAG) $(SRC) $(LIB)

%.o: %.c
	@echo "$(CY)[FT_LS] :$(CE) $(CG)Compiling $<$(CE)";
	@gcc $(FLAG) -c $< -o $@

start:
	@echo "\n\n"
	@echo "					$(CG)                          00000000000000000000$(CE)";
	@echo "					$(CG)                       00000000000000000000000000$(CE)";
	@echo "					$(CG)                    000000000000000000000000000000000         00   0000$(CE)";
	@echo "					$(CG)    000000        00000000000000000000000000000000000000       000000000$(CE)";
	@echo "					$(CG) 00 000000      0000000000    0000000000000    0000000000       0000000$(CE)";
	@echo "					$(CG) 000000000     0000000000      00000000000      00000000000    0000000$(CE)";
	@echo "					$(CG)   0000000    00000000000      00000000000      0000000000000000000000$(CE)";
	@echo "					$(CG)   00000000000000000000000    0000000000000    00000000000000  00000$(CE)";
	@echo "					$(CG)    000000000000000000000000000000000000000000000000000000000     000$(CE)";
	@echo "					$(CG)     000   000000000000000000000000000000000000000000000000000     0000$(CE)";
	@echo "					$(CG)    0000   000000000000000000000000000000000000000000000000000       000$(CE)";
	@echo "					$(CG)    000    0000000000000000000000000000000000000000000000 0000000000000000$(CE)";
	@echo "					$(CG)   0000000000000  0000000000000000000000000000000000000   00000000000000000$(CE)";
	@echo "					$(CG)   0000000000000   0000000000000000000000000000000000     00000000000$(CE)";
	@echo "					$(CG)  0000       0000    000000000000000000000000000000      000$(CE)";
	@echo "					$(CG)             00000     0000000000000000000000000         00$(CE)";
	@echo "					$(CG)               0000          000000000000000           000$(CE)";
	@echo "					$(CG)                00000                                0000$(CE)";
	@echo "					$(CG)                 000000      00000000000000        0000$(CE)";
	@echo "					$(CG)                   00000000     0000000000000   000000$(CE)";
	@echo "					$(CG)                      00000000000  0000000000000000$(CE)";
	@echo "					$(CG)                         000000000000000000000$(CE)";
	@echo "					$(CG)                                 00000000000000$(CE)";
	@echo "					$(CG)                                     00000000000$(CE)";
	@echo "					$(CG)                                      0000000000$(CE)";
	@echo "					$(CG)                                       0000000$(CE)";
	@echo "\n\n"
	@echo "							$(CG)     ______ _______     _       _____      $(CE)";
	@echo "							$(CG)    |  ____|__   __|   | |     / ____|     $(CE)";
	@echo "							$(CG)    | |__     | |      | |    | (___       $(CE)";
	@echo "							$(CG)    |  __|    | |      | |     \___ \      $(CE)";
	@echo "							$(CG)    | |       | |      | |____ ____) |     $(CE)";
	@echo "							$(CG)    |_|       |_|      |______|_____/      $(CE)";

clean: start
	@echo "$(CY)[FT_LS] :$(CE) $(CG)Cleaning Library ...$(CE)";
	-@make -C libft nohdclean
	@echo "$(CY)[FT_LS] :$(CE) $(CG)Cleaning ft_ls objects$(CE)";
	@/bin/rm -rf $(OBJ)

fclean: start clean
	@echo "$(CY)[FT_LS] :$(CE) $(CG)FCleaning Library ...$(CE)";
	-@make -C libft nohdfclean
	@echo "$(CY)[FT_LS] :$(CE) $(CG)Cleaning ft_ls ...$(CE)";
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
