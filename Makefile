CC = gcc

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

PATH_LIBFT = libft/

READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

LIBFT_A = $(PATH_LIBFT)/libft.a

FILES_C = parser/parser.c parser/parser_utils.c parser/parser_utils1.c parser/parser_utils2.c main_norm.c main.c\
	lexer/lexer.c lexer/lexer_utils.c lexer/lexer_utils2.c heredoc/heredoc.c heredoc/heredoc_utils.c\
	expander/expander.c expander/expander_utils.c expander/expander_utils1.c expander/expander_utils2.c\
	expander/expander_utils3.c execution/execution.c execution/execution_utils.c execution/execution_utils1.c\
	execution/execution_utils2.c execution/execution_utils3.c execution/execution_utils4.c execution/execution_utils5.c\
	execution/execution_utils6.c execution/execution_utils7.c builtins/ft_cd.c builtins/ft_cd_utils.c builtins/ft_echo.c\
	builtins/ft_env_utils.c builtins/ft_env_utils1.c builtins/ft_env.c builtins/ft_exit.c builtins/ft_export_utils.c\
	builtins/ft_export.c builtins/ft_pwd.c builtins/ft_unset.c

all: $(NAME)

$(NAME):$(FILES_C)
	make -C ./libft
	$(CC) $(CFLAGS) $(FILES_C) $(READLINE) $(LIBFT_A) -o $(NAME)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(LIBFT_A)

clean :
	rm -rf minishell.dSYM
	make clean -C $(PATH_LIBFT)

re: fclean all

.PHONY = clean fclean re all