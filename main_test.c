/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:32:27 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/12 15:30:49 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_std(t_minishell *minishell)
{
	dup2(minishell->out, 1);
	dup2(minishell->in, 0);
}


int shell_execute(t_minishell *minishell, t_command *command)
{
	if(command->full_args == NULL)
		return (1);
		
	if(strcmp(command->full_args[0], "exit") != 0)
		g_last_exec = 0;

	if(strcmp(command->full_args[0], "cd") == 0)
		return (shell_cd(command, minishell->env));
	else if (strcmp(command->full_args[0], "echo") == 0)
		return (shell_echo(command, minishell));
	else if (strcmp(command->full_args[0], "exit") == 0)
		return (shell_exit(command));
	else if (strcmp(command->full_args[0], "export") == 0)
		return (shell_export(command, minishell));
	else if (strcmp(command->full_args[0], "unset") == 0)
		return (shell_unset(command, minishell));
	else if (strcmp(command->full_args[0], "env") == 0)
		return (shell_env(minishell));
	else
		return shell_launch(minishell, command);
}


int	read_file(char* file_name)
{
	int fd;
    fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (fd);
}

int	create_empty_file(char* file_name)
{
	int fd;
    fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT | S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": Couldn't create the file\n", 2);
		return (-1);
	}
	return (fd);
}

int	create_append_file(char* file_name)
{
	int fd;
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND , S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": Couldn't create the file\n", 2);
		return (-1);
	}
	return (fd);
}


int loop_redirections(t_minishell *minishell, t_command *command)
{
	t_list *current;
	t_redirection *redirection;
	int status;
	int	fd;
	
	status = 1;
	current = command->redirections; 									// current =  redirection | redirection | redirection | redirection | ....

   	while(current != NULL) {

		redirection = (t_redirection*)current->content;
		if(redirection->type == LEFT_REDIR) 										// read from file (STDIN)
		{
			fd = read_file(redirection->file_name);
			if (fd < 0)
				return (-1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else 															// Write to a file (STDOUT)
		{
			if(redirection->type == RIGHT_REDIR)
				fd = create_empty_file(redirection->file_name);
			else
				fd = create_append_file(redirection->file_name);			 // append to file
			if (fd < 0)
				return (1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
      	current = current->next;
   	}
	if(command->full_args == NULL)
		reset_std(minishell);
	return (1);
}



int commands_loop(t_minishell *minishell, t_list *my_pipe)
{
   	t_list *current;
	int status;
	t_command *command;


	int commands_len = ft_lstsize(my_pipe);
	int **pipes_fd;
	int *forks;
	
	forks = malloc((commands_len + 1) * (sizeof(int)));
	pipes_fd = malloc((commands_len + 1) * (sizeof(int*)));

	int j = 0;
	while (j < (commands_len - 1))
	{
		pipes_fd[j] = malloc(2 * sizeof(int));
		
		if (pipe(pipes_fd[j]) == -1)
		{
			free(pipes_fd);
			free(forks);
			ft_putstr_fd("Minishell: Error in pipe\n", 2);
			return (1);
		}
		j++;
	}
	pipes_fd[j] = NULL;
	
	status = 1;
	current = my_pipe; // current = {command_0 | command | command | command | .... }
	int i = 0;
	int f = 0;

   	while(current != NULL)
	{
		command = (t_command*)current->content;

		forks[i] = fork();
		if (forks[i] < 0)
		{
			ft_putstr_fd("Minishell: Error in pipe\n", 2);
			free(forks);
			free_double_int(pipes_fd);
			return (1);
		}
		if (forks[i] == 0)
		{
			// Child process 
			if (i == 0) // first fork
			{
				dup2(pipes_fd[0][1], 1);
			}
			else if (i == (commands_len - 1)) // last fork
			{
				dup2(pipes_fd[i - 1][0], 0);
			}
			else
			{
				dup2(pipes_fd[i - 1][0], 0);
				dup2(pipes_fd[i][1], 1);
			}
			// close all pipes_fd
			f = 0;
			while (f < (commands_len - 1))
			{
				close(pipes_fd[f][0]);
				close(pipes_fd[f][1]);
				f++;
			}
			// handle redirections
			status = loop_redirections(minishell, command);
			if (status < 0)
			{
				// f = 0;
				// while (f < (commands_len - 1))
				// {
				// 	close(pipes_fd[f][0]);
				// 	close(pipes_fd[f][1]);
				// 	f++;
				// }
				exit(1);
				return (-1);
			}
			else if(status == 0)
			{
				free(forks);
				free_double_int(pipes_fd);
				return (1);
			}
			

			status = shell_execute(minishell, command);
			if(status == 0)
			{
				free(forks);
				free_double_int(pipes_fd);
				return (0);
			}
			exit(0);
		}
		i++;
      	current = current->next;
   	}
	f = 0;
	while (f < (commands_len - 1))
	{
		close(pipes_fd[f][0]);
		close(pipes_fd[f][1]);
		f++;
	}
	f = 0;
	while (f < commands_len)
	{
		waitpid(forks[f], &g_last_exec, 0);
		g_last_exec = WEXITSTATUS(g_last_exec);
		f++;
	}
	// wait(&g_last_exec);
	// g_last_exec = WEXITSTATUS(g_last_exec);
	
	free(forks);
	free_double_int(pipes_fd);
	return (1);
}

int commands_loop2(t_minishell *minishell, t_list *my_pipe)
{
   	t_list *current;
	int status;
	t_command *command;

	status = 1;
	command = (t_command*)my_pipe->content;
	status = loop_redirections(minishell, command);
	if(status < 0)
		return (-1);
	status = shell_execute(minishell, command);
	if(status == 0)
		return (0);
	reset_std(minishell);
	return (1);
}

int pipes_loop(t_minishell *minishell)
{
   	t_list *current;
	int status;
	t_list *my_pipe;

	status = 1;
	current = minishell->cmds; // command0 ( |  |  | ) ; command1 sdf | dfsf | sfs ; command2 ......
   	while(current != NULL) {
		my_pipe = current->content;
		scan_command(my_pipe, minishell->env);
		if(my_pipe->next == NULL) // if "--------;" has no pipe call commands_loop2
			status =  commands_loop2(minishell, my_pipe); // pipe | pipe | pipe | pipe | ....
		else
			status =  commands_loop(minishell, my_pipe); // pipe | pipe | pipe | pipe | ....
		if(status < 0)
		{
			g_last_exec = 1;
			// return (1);
		}
		else if(status == 0)
			return (0);
      	current = current->next;
   	}
	return (1);
}


void	ft_getline(char **line, t_data *data)
{
	int parsing_ret;
	int status;

	data->i = 0;
	write(1, PROMPT, ft_strlen(PROMPT));
	get_next_line(0, line);
	parsing_ret = parse_line(*line, data);
	if (parsing_ret == 0)
		status = pipes_loop(data->command);
	free_data(data);
}

int		main(int ac, char **av, char **env)
{
	int		i;
	t_data	*data;
	char	*line;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		exit_errno(ENOMEM);
	data->command = malloc(sizeof(t_minishell));
	if (!data->command)
		exit_errno(ENOMEM);
	set_env(env, data);
	data->command->out = dup(1);
	data->command->in = dup(0);
	while (1)
	{
		if (ac == 3 && !ft_strcmp(av[1], "-c"))
		{
			int parsing_ret;
			int status;
			line = av[2];
			parsing_ret = parse_line(line, data);
			if (parsing_ret == 0)
				status = pipes_loop(data->command);
			free_data(data);
			exit(0);
		}
		else
		{
			ft_getline(&line, data);
			free(line);
		}
	}
	i = 0;
	while (data->command->env[i])
		free(data->command->env[i++]);
	free(data->command->env);
	free(data->command);
	free(data);
}


