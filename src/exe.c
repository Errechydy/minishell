/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/04 16:33:04 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**get_paths(char **env)
{
	int		i;
	char	**paths;
	char	*tmp;

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

	tmp1 = ft_strjoin("/", command->execter);
	paths = get_paths(minishell->env);
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


int shell_launch(t_command *command, t_minishell *minishell)
{
	pid_t pid, wpid;
  	int status;
	char *execter;

	execter = found_exec(command, minishell);

	// printf("--> %s \n", execter);
  
	pid = fork();
    if (pid == 0)
    {
        char *const args[] = {execter, "-c", command->execter, NULL};
        if (execve(execter, command->full, minishell->env) == -1)
		{
			ft_putstr_fd("Shell: ", 1);
            ft_putstr_fd(strerror(errno), 1);
		}
	}
	else if (pid < 0) {
			ft_putstr_fd("Shell: Fork failed to create a new process \n", 1);
    }
	else {
		wait(&pid);
	}
	free(execter);
	return (1);
}


