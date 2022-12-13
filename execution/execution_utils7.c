/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kessalih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 02:20:21 by kessalih          #+#    #+#             */
/*   Updated: 2022/10/21 02:20:25 by kessalih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include "../includes/lexer.h"
#include "../includes/here_doc.h"
#include "../includes/execution.h"

int	ft_builtins(char *cmd, char **ar, t_env **env_t, char **envp)
{
	if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(ar, env_t));
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(envp, ar));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(ar, *env_t));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(env_t, ar));
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(ar));
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(ar));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	return (-1);
}

void	exec_one_c(t_data *data, int in, int out)
{
	set(&g_vars.exit, g_vars.exit);
	close(data->infile);
	close(data->outfile);
	dup2(out, 1);
	dup2(in, 0);
	close(out);
	close(in);
}

void	exec_one(t_command *command, t_data *data, t_env **env_t, char **envp)
{
	int	out;
	int	in;

	out = dup(1);
	in = dup(0);
	if (data->infile != -1)
		dup2(data->infile, 0);
	if (data->outfile != -1)
		dup2(data->outfile, 1);
	while (command && command->token != STRING)
		command = command->next;
	if (command && command->token == STRING)
	{
		g_vars.exit = ft_builtins(command->data, command->arr, env_t, envp);
		if (g_vars.exit != -1)
			exec_one_c(data, in, out);
		else
		{
			close(data->outfile);
			execute_cmd(command, data, env_t, envp);
		}
	}
}

void	exex_multi(t_command **cmd, t_data *data, t_env **env_t, char **envp)
{
	int	flag;

	while (data->pos != data->size)
	{
		flag = 0;
		get_files((*cmd), data);
		while ((*cmd) && (*cmd)->token != STRING && ((*cmd)->token != PIPE))
				(*cmd) = (*cmd)->next;
		if ((*cmd) && (*cmd)->token == STRING)
		{
			flag = 1;
			if (g_vars.err != 2)
				execute_cmd((*cmd), data, env_t, envp);
			data->pos++;
		}
		while ((*cmd) && (*cmd)->token != PIPE)
			(*cmd) = (*cmd)->next;
		if ((*cmd)->token == PIPE)
		{
			(*cmd) = (*cmd)->next;
			if (flag == 0)
				data->pos++;
			g_vars.err = 0;
		}
	}
}

void	exec(t_command *command, t_data *data, t_env **env_t, char **envp)
{
	int	flag;

	flag = 0;
	g_vars.err = 0;
	if (data->size > 0)
	{
		exex_multi(&command, data, env_t, envp);
		get_files(command, data);
		while (command && command->token != STRING && command->token != PIPE)
			command = command->next;
		if (command && command->token == STRING)
		{
			if (g_vars.err != 2)
				execute_cmd(command, data, env_t, envp);
		}
	}
	else
	{
		get_files(command, data);
		if (g_vars.err != 2)
			exec_one(command, data, env_t, envp);
	}
}
