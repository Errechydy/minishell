/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/10 15:16:23 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void echo_display(char **full_args, int skip_n)
{
	int i;

	if (skip_n == 1)
		i = 2;
	else
		i = 1;
	while(full_args[i] != NULL)
	{
		ft_putstr_fd(full_args[i], 1);
		if(full_args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int shell_echo(t_command *command, t_minishell *minishell)
{
	if (command->full_args[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
	}
	else if(ft_strcmp(command->full_args[1], "-n") == 0)
	{
		echo_display(command->full_args, 1);
	}
	else
	{
		echo_display(command->full_args, 0);
		ft_putstr_fd("\n", 1);
	}
    g_last_exec = 0;
	return (1);
}
