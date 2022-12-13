/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:30:22 by oaissoun          #+#    #+#             */
/*   Updated: 2022/09/09 14:30:23 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/here_doc.h"
#include "../includes/expander.h"
#include "../includes/parser.h"

int	execute_heredoc(t_command *cmd, char **env)
{
	while (cmd)
	{
		if (cmd->err == 1)
			break ;
		if (cmd->token == HEREDOC)
		{
			cmd->heredoc = here_doc(cmd->data, env);
			if (cmd->heredoc == -2)
				return (-1);
		}
		cmd = cmd->next;
	}
	return (0);
}
