/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:32:27 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/13 18:04:22 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_std(t_minishell *minishell)
{
	dup2(minishell->out, 1);
	dup2(minishell->in, 0);
}

int		shell_execute(t_minishell *minishell, t_command *command)
{
	if (command->full_args == NULL)
		return (1);
	if (strcmp(command->full_args[0], "exit") != 0)
		g_exist.last_exec = 0;
	if (strcmp(command->full_args[0], "cd") == 0)
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
		return (shell_launch(minishell, command));
}

int		read_file(char *file_name)
{
	int	fd;

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

int		create_empty_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT | S_IRUSR
			| S_IRGRP | S_IWGRP | S_IWUSR, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": Couldn't create the file\n", 2);
		return (-1);
	}
	return (fd);
}

int		create_append_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND | S_IRUSR
			| S_IRGRP | S_IWGRP | S_IWUSR, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": Couldn't create the file\n", 2);
		return (-1);
	}
	return (fd);
}
