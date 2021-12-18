# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: estoffel <estoffel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 19:55:45 by estoffel          #+#    #+#              #
#    Updated: 2021/12/07 23:12:56 by estoffel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror

INCLUDES =	-Llibft/ -lft

SRC		=	main.c				\
			utils.c				\

BNS		=	main_bonus.c		\
			heredoc_bonus.c		\
			multipipes_bonus.c	\
			utils_bonus.c		\

OBJ		=	$(addprefix ./sources/,$(SRC:%.c=%.o))

OBJBNS	=	$(addprefix ./sources/,$(BNS:%.c=%.o))

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ) ./libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -Llibft -lft

bonus:	$(OBJBNS) ./libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJBNS) -Llibft -lft
	touch $@

./libft/libft.a:
	make $(@F) -C $(@D)

clean:
	$(RM) $(OBJ) $(OBJBNS)
	make $@ -C ./libft/

fclean:
	$(RM) $(OBJ) $(OBJBNS)
	$(RM) $(NAME) a.out bonus
	make $@ -C ./libft/

re:		fclean all

.PHONY:	all clean fclean re