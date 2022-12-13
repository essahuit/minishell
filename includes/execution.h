/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaissoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:49:03 by oaissoun          #+#    #+#             */
/*   Updated: 2022/09/28 13:49:04 by oaissoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXECUTION_H
# define EXECUTION_H

# include "./lexer.h"
# include "./parser.h"

typedef struct s_env
{
	char			*first;
	char			*second;
	struct s_env	*next;
}	t_env;

typedef struct exp
{
	char	*first;
	char	*second;
}	t_exp;

typedef struct s_data
{
	int		size;
	int		pos;
	char	**env;
	int		**fd;
	int		infile;
	int		reserv;
	int		outfile;
}	t_data;

void	ft_perror(int x, char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strstr(char *str, char *to_find);
char	*ft_path(char **envp);
void	ft_free_two(char **ar);
char	*ft_checkaccess(char *cmd, char **cm);
char	*ft_free_one(char *s1, char *s2);
char	*ft_access(char *cmd, char **arpath);
char	*ft_strdup(const char *s1);
size_t	ft_len(char const *s, char c);
void	ft_free(char **ar, size_t k);
void	ft_size(char **ar, const char *s, char c);
char	**ft_split1(char const *s, char c);
int		ft_len_ar(char **ar);
char	**ft_ar(char **arr, char *cmd);
void	child_proc(t_command *cmd, t_data *data, t_env **env_t, char **envp);
void	execute_cmd(t_command *cmd, t_data *data, t_env **env_t, char **envp);
void	closing(t_data *data);
int		ft_lstcommandsize(t_command *command);
int		ft_redir(char *data, int token);
void	execute(t_command *command, char **envp, t_env **env_t);
void	ft_add_env(t_env **env, char *envp);
t_env	*ft_last_env(t_env *env);
t_env	*ft_cenv(char *envp, int *j);
int		get_findex(char *env);
int		ft_export(char **ar, t_env **env);
int		ft_size_env(t_env *env);
int		ft_env(char **env, char **ar);
int		ft_echo(char **ar);
int		ft_builtins(char *cmd, char **ar, t_env **env_t, char **envp);
int		ft_cd(char **ar, t_env *env);
int		ft_pwd(void);
int		ft_unset(t_env **env_t, char **ar);
int		ft_check_var(char *temp);
int		ft_exit(char **ar);
void	set_vars(t_env *env_t);
int		ft_pid_exec(t_command *command);
t_env	*init_envt(char	**envp);
int		ft_size_env(t_env *env);
char	**conv_env(t_env *env);
char	**ft_set_env(char **env, t_env *env_t);
void	exec(t_command *command, t_data *data, t_env **env_t, char **envp);
void	get_files(t_command *command, t_data *data);
void	ft_var_perr(char *str);
void	ft_var_free(char **ar, char *temp);
char	*ft_var(char *envp, int *j);
t_env	*ft_cenv(char *envp, int *j);
int		get_findex(char *env);
char	*ft_strdup2(char *el, int *j);
int		ft_isalnumic(int c);
int		ft_check_var(char *temp);
void	ft_free_ar(char **ar);
t_exp	**conv_exp(t_env *env);
t_env	*ft_cenv_e(char **ar);
void	ft_free_exp(t_exp **exp);
void	ft_export_p(t_exp **exp);
int		ft_export_l(char **ar);
char	*ft_env_path(t_env *env, char *first);
void	ft_free_cd(char *path, char *oldpwd, char *get);
void	ft_cd_c_l(char *s, char *path, int *x);
void	ft_free_env(t_env *env);
void	init_vars_access(int *i, char **ocmd);
#endif