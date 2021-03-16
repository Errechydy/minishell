/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/16 19:37:09 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void export_invalid_arg_msg(char *arg)
{
	ft_putstr_fd("Minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exist.last_exec = 1;
}

int	arg_has_equal(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if(arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void  export_varible(char *arg, t_minishell *minishell)
{
	char **new_env;
	int i;
	
	new_env = (char **)malloc(sizeof(char *) * (words_counter(minishell->env) + 1));
	i = 0;
	while (minishell->env[i] != NULL)
	{
		new_env[i] = ft_strdup(minishell->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[++i] = NULL;
	free_double(minishell->env);
	minishell->env = new_env;
}

int		shell_export(t_command *command, t_minishell *minishell)
{
	int i;

	i = 1;
	while (command->full_args[i] != NULL)
	{
		if(valid_arg(command->full_args[i]) == 1)
			export_invalid_arg_msg(command->full_args[i]);
		else if (arg_exist(command->full_args[i], minishell) == 1 || (arg_has_equal(command->full_args[i]) == 1)) // var doesn't exist OR var has value
			export_varible(command->full_args[i], minishell);
		i++;
	}
	return (1);
}
