/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/14 18:30:27 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		vars_counter_(char **new_vars, char **env)
{
	int	i;
	int	j;
	int	counter;

	counter = 0;
	i = 0;
	while (new_vars[i] != NULL)
	{
		j = 0;
		while (env[j] != NULL)
		{
			if (env_compair(new_vars[i], env[j]) == 1)
				counter++;
			j++;
		}
		i++;
	}
	return (counter);
}

int		is_valid_arg2(char *arg, int show_error)
{
	if (arg_start_with_char(arg) == 0)
	{
		return (1);
	}
	else
	{
		if (show_error == 1)
		{
			ft_putstr_fd("Minishell: unset: '", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exist.last_exec = 1;
		}
		return (0);
	}
	return (0);
}

int		count_valid_args2(char **args)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (is_valid_arg2(args[i], 0) == 0)
			len++;
		i++;
	}
	return (len);
}
