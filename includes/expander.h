/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:53:23 by oaissoun          #+#    #+#             */
/*   Updated: 2022/08/08 16:53:25 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXPANDER_H
# define EXPANDER_H

# include "./parser.h"

char	**init_env(char	**envp);
char	*expand_str(char *str, char	**envp);
char	*expand_(char *str, char **envp);
int		expand_dquote(char *str, char **ret, int i, char **envp);
int		expand_squote(char *str, char **ret, int i);
int		expand_dollar(char *str, char **ret, int i, char **envp);
char	*remove_quote(char *str);
void	expand_command(t_command *cmd, char	**envp);
int		remove_quote_norm(int i, char quote, char *str, char **ret);
int		ft_check(int c);
int		roll_back(int i, char *str);
void	expand_dquote_join(char ***ret, char *str, int i);
int		expand_dquote_status(char ***ret, int i);
void	expand_dquote_join_sq(char ***ret, char *str, int i);
void	expand_dquote_join_char(char ***ret, char *str, int i);
int		expand_dquote_(char ***ret, char *str, int i, char **envp);

#endif