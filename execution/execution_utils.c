/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:19:21 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:19:24 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	execute_cmd_first(t_data *data)
{
	if (data->infile != -1)
		dup2(data->infile, 0);
	if (data->outfile != -1)
		dup2(data->outfile, 1);
	else
		dup2(data->fd[data->pos][1], 1);
}

void	execute_cmd_mid(t_data *data)
{
	if (data->infile != -1)
		dup2(data->infile, 0);
	else
		dup2(data->fd[data->pos - 1][0], 0);
	if (data->outfile != -1)
		dup2(data->outfile, 1);
	else
		dup2(data->fd[data->pos][1], 1);
}

void	execute_cmd_last(t_data *data)
{
	if (data->outfile != -1)
		dup2(data->outfile, 1);
	if (data->infile != -1)
		dup2(data->infile, 0);
	else
		dup2(data->fd[data->pos - 1][0], 0);
}

void	execute_cmd_one(t_data *data)
{
	if (data->infile != -1)
	{
		dup2(data->infile, 0);
		close(data->infile);
	}
	if (data->outfile != -1)
	{
		dup2(data->outfile, 1);
		close(data->outfile);
	}
}

void	execute_cmd(t_command *cmd, t_data *data, t_env **env_t, char **envp)
{
	int	pid;

	pid = fork();
	if (cmd->token == STRING && ft_pid_exec(cmd) && pid != 0)
		g_vars.pid = pid;
	if (pid == -1)
		ft_perror(2, "");
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (data->size > 0)
		{
			if (data->pos == 0)
				execute_cmd_first(data);
			else if (data->pos > 0 && data->pos < data->size)
				execute_cmd_mid(data);
			else if (data->pos == data->size)
				execute_cmd_last(data);
			closing(data);
		}
		else
			execute_cmd_one(data);
		if (cmd)
			child_proc(cmd, data, env_t, envp);
	}
}
