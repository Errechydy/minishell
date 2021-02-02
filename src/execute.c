/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/02 15:33:01 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int shell_launch(t_minishell minishell)
// {
// 	pid_t pid;
  
// 	pid = fork();
//     if (!pid)
//     {
//         char *binaryPath = "/bin/bash";
//         char *const args[] = {binaryPath, "-c", *minishell.command, NULL};
//         if (execve(binaryPath, args, minishell.env) == -1)
//             ft_putstr_fd(strerror(errno), 1);
//         // else
//         //     path->dollar = 1;
        
//     } 
// 	return (1);
// }

// int shell_launch(t_minishell minishell)
// {
//   pid_t pid, wpid;
//   int status;

//   pid = fork();
//   if (pid == 0) {
//     // Child process
//     if (execvp(minishell.command[0], minishell.command) == -1) {
//       perror("lsh");
//     }
//     exit(EXIT_FAILURE);
//   } else if (pid < 0) {
//     // Error forking
//     perror("lsh");
//   } else {
//     // Parent process
//     do {
//       wpid = waitpid(pid, &status, WUNTRACED);
//     } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//   }

//   return (1);
	
// }


// int shell_launch(t_minishell minishell)
// {
//   pid_t pid, wpid;
//   int status;

//   pid = fork();
//   if (pid == 0) {
//     // Child process
//     if (execvp(minishell.command[0], minishell.command) == -1) {
//       perror("lsh");
//     }
//     exit(EXIT_FAILURE);
//   } else if (pid < 0) {
//     // Error forking
//     perror("lsh");
//   } else {
//     // Parent process
//     do {
//       wpid = waitpid(pid, &status, WUNTRACED);
//     } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//   }
//   return (1);
// }

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

char *found_exec(t_minishell minishell)
{
	char	**paths;
	int i;
	struct stat     stbf;
	struct stat     *statbuf;
	char *tmp1;
	char *execter;

	tmp1 = ft_strjoin("/", minishell.command[0]);
	paths = get_paths(minishell.env);
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
		i++;
	}
	free(tmp1);
	free_double(paths);
	return (NULL);
}
/*
int shell_launch(t_minishell minishell)
{
	pid_t pid, wpid;
  	int status;
	char *execter;

	execter = found_exec(minishell);

	if(!execter)
	{
		ft_putstr_fd("Shell: couldn't found ", 1);
		ft_putstr_fd(minishell.command[0], 1);
		ft_putstr_fd("\n", 1);
		// free(execter);
		// return (1);
	}


	  // stat

	//   printf("--> %s \n", execter);
	//   printf("--> %s \n", minishell.env.);
  
	pid = fork();
    if (pid == 0)
    {
        // char *binaryPath = "/bin/bash";
        char *binaryPath = execter;
        // char *const args[] = {binaryPath, "-c", *minishell.command, NULL};
        char *const args[] = {binaryPath, *minishell.command, NULL};
        if (execve(binaryPath, args, minishell.env) == -1)
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
	// free(execter);
	return (1);
}
*/


int shell_launch(t_minishell minishell)
{
	pid_t pid, wpid;
  	int status;
	char *execter;

	execter = found_exec(minishell);

	// if(!execter)
	// {
	// 	ft_putstr_fd("Shell: couldn't found ", 1);
	// 	ft_putstr_fd(minishell.command[0], 1);
	// 	ft_putstr_fd("\n", 1);
	// 	free(execter);
	// 	return (1);
	// }


	  // stat

	  printf("--> %s \n", execter);
	//   return (1);
	//   printf("--> %s \n", minishell.env.);
  
	pid = fork();
    if (pid == 0)
    {
        // char *binaryPath = "/bin/bash";
        // char *const args[] = {binaryPath, "-c", *minishell.command, NULL};
        // if (execve(binaryPath, args, minishell.env) == -1)


		// char *cmd_args[] = {"stty", "-echoctl", 0};
		// 	char *env[] = {" ", "env", 0};
		// 	;
        // if (execve(*minishell.command[0], cmd_args, env) == -1)
        
        char *const args[] = {execter, "-c", *minishell.command, NULL};
        // char *const args[] = {execter, *minishell.command, NULL};
        if (execve(execter, minishell.command, minishell.env) == -1)
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
	// free(execter);
	return (1);
}

int shell_execute(t_minishell minishell)
{
	if(strcmp(minishell.command[0], "cd") == 0)
		return (shell_cd(minishell.command));
	else if (strcmp(minishell.command[0], "echo") == 0)
		return (shell_echo(minishell.command));
	else if (strcmp(minishell.command[0], "exit") == 0)
		return (shell_exit(minishell.command));
	else if (strcmp(minishell.command[0], "export") == 0)
		return (shell_export(minishell));
	return shell_launch(minishell);
}
