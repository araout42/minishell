# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pemora <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/08 21:44:42 by pemora            #+#    #+#              #
#    Updated: 2019/04/14 15:00:59 by araout           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= minishell

CC		=	gcc

FLAGS 	=  -Wall -Wextra -Werror

SRCS 	=	srcs/built_in.c				\
			srcs/exec_cmd.c				\
			srcs/ft_cd.c				\
			srcs/ft_errors.c			\
			srcs/ft_exit.c				\
			srcs/ft_misc.c				\
			srcs/ft_parsing.c			\
			srcs/ft_set_env.c			\
			srcs/ft_signal.c				\
			srcs/minishell.c			\


LIBFT 	=	libft

OBJS 	= $(SRCS:.c=.o)

all: lib $(NAME)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)/libft.a

lib:
		make -C $(LIBFT)

clean:
		/bin/rm -rf $(OBJS)
		make -C $(LIBFT) clean

cleannolib:
		/bin/rm -rf $(OBJS)


fclean:		cleannolib
		/bin/rm -rf $(NAME)
		make -C $(LIBFT) fclean

if:
	if make; then make clean && clear; fi

re: fclean all
