# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/28 14:03:26 by jtranchi          #+#    #+#              #
#    Updated: 2016/02/06 08:13:47 by jtranchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
LIB = libft/libft.a
SRC =	src/ls.c \
		src/errors.c \
		src/openread.c \
		src/ls-l.c \
		src/options.c
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
	@gcc -g -o $(NAME) $(FLAG) $(SRC) $(LIB)

%.o: %.c
	@echo "$(CY)[FT_LS] :$(CE) $(CG)Compiling $<$(CE)";
	@gcc $(FLAG) -c $< -o $@
	
src/ft_ls.c: start

start:
	@echo "\n\n"
	@echo "						$(CG)		           ¶¶¶¶¶¶¶¶¶¶¶              $(CE)";
	@echo "						$(CG)		         ¶¶           ¶¶            $(CE)";
	@echo "						$(CG)		       ¶¶               ¶¶          $(CE)";
	@echo "						$(CG)		     ¶¶      $(CY)¶¶$(CE)    $(CY)¶¶$(CE)     $(CG)¶¶        $(CE)";
	@echo "						$(CG)		   ¶¶       $(CY)¶¶$(CE)    $(CY)¶¶$(CE)        $(CG)¶¶      $(CE)";
	@echo "						$(CG)		 ¶¶          $(CY)¶¶$(CE)    $(CY)¶¶$(CE)         $(CG)¶¶    $(CE)";
	@echo "						$(CG)		¶¶                             ¶¶   $(CE)";
	@echo "						$(CG)		¶¶                             ¶¶ $(CE)";
	@echo "						$(CG)		¶¶     $(CY)¶¶$(CE)              $(CY)¶¶$(CE)      $(CG)¶¶ $(CE)";
	@echo "						$(CG)		¶¶      $(CY)¶¶$(CE)            $(CY)¶¶$(CE)       $(CG)¶¶ $(CE)";
	@echo "						$(CG)		¶¶       $(CY)¶¶$(CE)         $(CY)¶¶$(CE)         $(CG)¶¶   $(CE)";
	@echo "						$(CG)		 ¶¶         $(CY)¶¶¶¶¶¶¶$(CE)           $(CG)¶¶    $(CE)";
	@echo "						$(CG)		   ¶¶                        ¶¶     $(CE)";
	@echo "						$(CG)		     ¶¶                    ¶¶       $(CE)";
	@echo "						$(CG)		       ¶¶                ¶¶         $(CE)";
	@echo "						$(CG)		         ¶¶            ¶¶           $(CE)";
	@echo "						$(CG)		           ¶¶¶¶¶¶¶¶¶¶¶¶             $(CE)";
	@echo "\n\n"
	@echo "							$(CY) - - - - - - - - - - - - - - - - - - - - - -$(CE)";
	@echo "							$(CY)|$(CE)$(CG)     ______ _______     _       _____      $(CE)$(CY)|$(CE)";
	@echo "							$(CY)|$(CE)$(CG)    |  ____|__   __|   | |     / ____|     $(CE)$(CY)|$(CE)";
	@echo "							$(CY)|$(CE)$(CG)    | |__     | |      | |    | (___       $(CE)$(CY)|$(CE)";
	@echo "							$(CY)|$(CE)$(CG)    |  __|    | |      | |     \___ \      $(CE)$(CY)|$(CE)";
	@echo "							$(CY)|$(CE)$(CG)    | |       | |      | |____ ____) |     $(CE)$(CY)|$(CE)";
	@echo "							$(CY)|$(CE)$(CG)    |_|       |_|      |______|_____/      $(CE)$(CY)|$(CE)";
	@echo "							$(CY) - - - - - - - - - - - - - - - - - - - - - -$(CE)";

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
