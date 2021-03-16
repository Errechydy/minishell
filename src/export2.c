/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/16 17:28:17 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		env_compair(char *var1, char *var2)
{
	int		res;
	char	**str1;
	char	**str2;

	res = 0;
	str1 = ft_split(var1, '=');
	str2 = ft_split(var2, '=');
	if (ft_strcmp(str1[0], str2[0]) == 0)
		res = 1;
	free_double(str1);
	free_double(str2);
	return (res);
}

int		vars_counter_and_update(char **new_vars, char **env)
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
			{
				free(env[j]);
				env[j] = ft_strdup(new_vars[i]);
				counter++;
			}
			j++;
		}
		i++;
	}
	counter = words_counter(new_vars) - counter;
	return (counter);
}

int		var_exist(char *var, char **env)
{
	int j;

	j = 0;
	while (env[j] != NULL)
	{
		if (env_compair(var, env[j]) == 1)
			return (1);
		j++;
	}
	return (0);
}

char	**get_new_env(char **new_vars, char **env, int len)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	j = 0;
	while (new_vars[i] != NULL)
	{
		if (var_exist(new_vars[i], env) == 0)
		{
			new_env[j] = ft_strdup(new_vars[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int		arg_has_equal(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((int)str[i] == 61)
			return (1);
		i++;
	}
	return (0);
}
