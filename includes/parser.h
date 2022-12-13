/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 12:07:32 by oaissoun          #+#    #+#             */
/*   Updated: 2022/06/16 12:07:33 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./lexer.h"

typedef struct s_command
{
	char				*data;
	int					token;
	char				**arr;
	int					heredoc;
	int					err;
	int					pid;
	struct s_command	*next;
}	t_command;

t_command	*create_list(char *data, int i);
void		add_to_list(t_command *lst, char *data, int i);
void		print_list(t_command *cmd);
void		concat_lists(t_command *lst, t_command *lst1);
void		eat(t_lexer *lexer, int i);
t_command	*operator(t_lexer *lexer);
t_command	*command_(t_lexer *lexer);
t_command	*list(t_lexer *lexer);
char		**add_to_arr(char **arr, char *str);
char		**init_arr(char	*str);
size_t		ft_strlen2(char	**s);
void		last_touches(t_command	*cmd);
void		siginthandle(int signal);
void		free_d_arr(char **arr);
int			is_operator(t_lexer *lexer);

#endif