/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 10:50:06 by oaissoun          #+#    #+#             */
/*   Updated: 2022/09/03 10:50:07 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/expander.h"
#include "./includes/lexer.h"
#include "./includes/here_doc.h"
#include "./includes/execution.h"

void	free_cmd(t_command **cmd);
void	free_all(char *input, t_command **command, t_lexer **lexer);
char	*ft_main(int argc, char *argv[]);
void	free_all_syn(char *input, t_lexer **lexer);

void	init_main(t_env **env_t, char **envp, char ***env)
{
	*env_t = init_envt(envp);
	*env = NULL;
	g_vars.home = NULL;
	g_vars.pwd = NULL;
	set(&g_vars.exit, 0);
	set_vars(*env_t);
}

void	set_signals(void)
{
	signal(SIGINT, siginthandle);
	signal(SIGQUIT, SIG_IGN);
	g_vars.exp_f = 0;
}

int	expandnexecute(char ***env, t_env **env_t, t_command **cmd, t_lexer **lexer)
{
	expand_command(*cmd, *env);
	if (execute_heredoc(*cmd, *env) == -1)
	{
		printf("\n");
		free_all(g_vars.input, cmd, lexer);
		return (1);
	}
	last_touches(*cmd);
	if (ft_strlen(g_vars.input) > 0)
		execute(*cmd, *env, env_t);
	return (0);
}

int	lexernheredoc(char ***env, t_lexer **lexer, t_env **env_t, t_command **cmd)
{
	*env = ft_set_env(*env, *env_t);
	*lexer = init_lexer(g_vars.input);
	if ((*lexer)->syn == 2)
	{
		free_all_syn(g_vars.input, lexer);
		return (1);
	}
	*cmd = list(*lexer);
	if (ft_strlen(g_vars.input))
		add_history(g_vars.input);
	if ((*lexer)->syn == 1)
	{
		if (execute_heredoc(*cmd, *env) == -1)
		{
			free_all(g_vars.input, cmd, lexer);
			return (1);
		}
		free_all(g_vars.input, cmd, lexer);
		ft_throw_error("syntax error");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_lexer		*lexer;
	t_command	*command;
	char		**env;
	t_env		*env_t;

	init_main(&env_t, envp, &env);
	while (1)
	{
		set_signals();
		g_vars.input = ft_main(argc, argv);
		if (g_vars.input)
		{
			if (lexernheredoc(&env, &lexer, &env_t, &command) == 1)
				continue ;
			if (lexer->syn == 0)
			{
				if (expandnexecute(&env, &env_t, &command, &lexer) == 1)
					continue ;
			}
			free_all(g_vars.input, &command, &lexer);
		}
		else
			exit(g_vars.exit);
	}
	return (0);
}
