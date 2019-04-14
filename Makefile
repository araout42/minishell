NAME = minishell

CFLAGS = -Wall -Wextra -Werror

HEADERS = 	srcs/minishell.h\
			libft/libft.h\

SOURCES = 	srcs/minishell.c\
			srcs/exec_cmd.c\
			srcs/built_in.c\
			srcs/ft_set_env.c\
			srcs/ft_cd.c\
			srcs/ft_exit.c\
			srcs/ft_errors.c\
			srcs/ft_parsing.c\
			srcs/ft_signal.c\
			srcs/ft_misc.c\

OBJECT = $(SOURCES:.c=.o)


all: $(NAME)
		make -C libft/

$(NAME): $(OBJECT)
		gcc -o $@ $(CFLAGS) $(OBJECT) libft/libft.a



clean:
		rm -rf $(OBJECT)
		make -C libft clean

fclean: clean
		rm -rf $(NAME)
		make -C libft fclean

re: fclean all

.PHONY: re fclean clean all
