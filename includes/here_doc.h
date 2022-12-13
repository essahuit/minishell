/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:41:46 by oaissoun          #+#    #+#             */
/*   Updated: 2022/09/09 15:41:48 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "../includes/lexer.h"
# include "../includes/parser.h"

int		len_calc(char *str1, char *str2);
int		here_doc(char *lim, char **env);
int		is_string(char *str);
int		execute_heredoc(t_command *cmd, char **env);
void	ft_write(int *fd, char *input);
void	exec_child_heredoc(int *fd, char *lim, char **env);

#endif