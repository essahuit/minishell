/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:19:59 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:20:02 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

int	ft_lstcommandsize(t_command *command)
{
	int	i;

	i = 0;
	while (command)
	{
		if (command->token == PIPE)
			i++;
		command = command->next;
	}
	return (i);
}

void	closing(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->size)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		free(data->fd[i]);
		i++;
	}
	free(data->fd);
}

void	child_proc(t_command *cmd, t_data *dataa, t_env **env_t, char **envp)
{
	char	*path;
	char	**arpath;
	char	*cmdexec;
	char	**ar;
	int		x;

	if (cmd->token == STRING)
	{
		ar = ft_ar(cmd->arr, cmd->data);
		path = ft_strdup(ft_path(dataa->env) + 5);
		arpath = ft_split1(path, ':');
		cmdexec = ft_access(cmd->data, arpath);
		x = ft_builtins(cmd->data, cmd->arr, env_t, envp);
		if (x != -1)
		{
			set(&g_vars.exit, x);
			exit(x);
		}
		if (execve(cmdexec, ar, dataa->env) == -1)
		{
			dup2(g_vars.reserv, 1);
			ft_perror(0, cmd->data);
		}
	}
}

int	ft_pid_exec(t_command *command)
{
	while (command)
	{
		command = command->next;
		if (command && command->token == STRING)
			return (0);
	}
	return (1);
}

void	init_vars_access(int *i, char **ocmd)
{
	*i = -1;
	*ocmd = NULL;
}
