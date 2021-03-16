/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/16 17:28:23 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_is_userscore(int c)
{
	if (c == 95)
		return (1);
	return (0);
}

int		arg_start_with_char(char *str)
{
	int i;

	if (ft_isdigit(str[0]) == 1)
		return (1);
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) != 1 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int		count_valid_args(char **args)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (is_valid_arg(args[i], 0) == 0)
			len++;
		i++;
	}
	return (len);
}

char	**set_valid_envs(t_command *command)
{
	int		i;
	int		j;
	char	**new_env;
	int		len;

	len = count_valid_args(&(command->full_args[1]));
	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	i = 1;
	j = 0;
	while (command->full_args[i] != NULL)
	{
		if (is_valid_arg(command->full_args[i], 1) == 1)
		{
			new_env[j] = ft_strdup(command->full_args[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	display_env_chars(char *env)
{
	int len;
	int i;
	int first;

	first = 0;
	len = ft_strlen(env);
	i = 0;
	while (i < len)
	{
		if ((env[i] == 61) && (first == 0))
		{
			ft_putchar_fd(env[i], 1);
			ft_putchar_fd('"', 1);
			first = 1;
		}
		else if ((i + 1) == len)
		{
			ft_putchar_fd(env[i], 1);
			if (first == 1)
				ft_putchar_fd('"', 1);
		}
		else
			ft_putchar_fd(env[i], 1);
		i++;
	}
}
