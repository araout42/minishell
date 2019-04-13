NAME = minishell

CFLAGS = -Wall -Wextra -Werror

HEADERS = 	srcs/ft_ls.h\
			libft/libft.h\

LIB = libft/

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

$(NAME): $(LIB) $(OBJECT)
		make -C libft/
		gcc -o $(NAME) $(CFLAGS) $(OBJECT) libft/libft.a -L./libft

all: $(NAME)

clean:
		rm -rf $(OBJECT)
		make -C libft clean

fclean: clean
		rm -rf $(NAME)
		make -C libft fclean

re: fclean all
