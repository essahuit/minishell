/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:18:27 by oaissoun          #+#    #+#             */
/*   Updated: 2022/06/13 12:18:30 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_vars
{
	char	*pwd;
	char	*home;
	int		err;
	int		pid;
	int		exit;
	int		exp_f;
	int		reserv;
	char	**tmp;
	char	*input;
}	t_vars;

t_vars	g_vars;

typedef struct token{
	enum
	{
		STRING,
		LREDIR,
		RREDIR,
		PIPE,
		HEREDOC,
		APPENDREDIR,
		DOLLAR,
		END
	}e_type;
	char	*value;
}	t_token;

typedef struct s_lexer
{
	char	*content;
	int		i;
	char	c;
	int		syn;
	t_token	*token;

}	t_lexer;

t_lexer	*init_lexer(char *content);
void	lexer_advance(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);
t_token	*create_token(int type, char *value);
t_token	*get_(t_lexer *lexer, int i, char *val);
t_token	*get_next_token(t_lexer *lexer);
int		my_ft_isprint(int c, char except);
void	ft_throw_error(char	*err);
char	*join_char(char c, char *str);
t_token	*get_string(t_lexer *lexer);
t_token	*get_next_token2(t_lexer *lexer);
int		is_quote(char c);
void	set(int *var, int val);

#endif