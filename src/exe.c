/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/12 16:49:13 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**get_paths(char **env)
{
	int		i;
	char	**paths;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while(env[i] != NULL)
	{
		if(ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			tmp = &*(env[i] + 5);
			break ;
		}
		i++;
	}
	if(tmp == NULL)
		return (NULL);
	paths = ft_split(tmp, ':');
	while(env[i] != NULL)
	{
		if(ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			tmp = &*(env[i] + 5);
			break ;
		}
		i++;
	}
	return (paths);
}

char *found_exec(t_command *command, t_minishell *minishell)
{
	char	**paths;
	int i;
	struct stat     stbf;
	struct stat     *statbuf;
	char *tmp1;
	char *execter;

	tmp1 = ft_strjoin("/", command->full_args[0]);

	paths = get_paths(minishell->env);
	if(paths == NULL)
		return (NULL);
	statbuf = &stbf;
	i = 0;
	while(paths[i] != NULL)
	{
		execter = ft_strjoin(paths[i], tmp1);
		if(stat(execter, statbuf) == 0)
		{
			free(tmp1);
			free_double(paths);
			return (execter);
		}
		free(execter);
		i++;
	}
	free(tmp1);
	free_double(paths);
	return (NULL);
}

int ft_str_has_char(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s) + 1;
	while (s_len--)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}


int shell_launch(t_minishell *minishell, t_command *command)
{
	pid_t pid, wpid;
  	int status;
	char *execter;

	// ft_putstr_fd(" =====> ", 2);
	// ft_putstr_fd(command->full_args[0], 2);
	// ft_putstr_fd("\n", 2);

	// return (1);
	
	if(ft_str_has_char(command->full_args[0], '/') == 0)
		execter = found_exec(command, minishell);
	else
		execter = command->full_args[0];

	if (execter == NULL)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command->full_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_last_exec = 127;
		return (1);
	}
  
	pid = fork();
    if (pid == 0)
    {
        char *const args[] = {execter, "-c", command->full_args[0], NULL};
        if (execve(execter, command->full_args, minishell->env) == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
            ft_putstr_fd(command->full_args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			g_last_exec = 127;
		}
		else
			g_last_exec = 0;
		exit(0);
	}
	else if (pid < 0)
	{
		ft_putstr_fd("Minishell: Fork failed to create a new process \n", 2);
		g_last_exec = 127;
    }
	// wait(&g_last_exec);
	// g_last_exec = WEXITSTATUS(g_last_exec);

	waitpid(pid, &g_last_exec, 0);
	g_last_exec = WEXITSTATUS(g_last_exec);

	if(ft_str_has_char(command->full_args[0], '/') == 0)
		free(execter);
	return (1);
}


