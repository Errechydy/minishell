/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:09:53 by hrhirha           #+#    #+#             */
/*   Updated: 2021/03/16 17:01:20 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_env(char **s, t_data *data)
{
	int x;
	int	i;

	x = 0;
	while (s[x])
		x++;
	data->command->env = malloc((x + 1) * sizeof(char *));
	if (!data->command->env)
		exit_errno(ENOMEM);
	i = 0;
	while (i < x)
	{
		data->command->env[i] = ft_strdup(s[i]);
		i++;
	}
	data->command->env[i] = NULL;
}

int		search_env(char *key, char **env, int i, int *j)
{
	char *env_key;

	*j = 0;
	while (env[i][*j] != '=')
		*j += 1;
	env_key = ft_substr(env[i], 0, *j);
	if (ft_strcmp(key, env_key) == 0)
	{
		free(env_key);
		return (0);
	}
	free(env_key);
	return (1);
}

char	*get_env_value(char *key, char **env)
{
	char	*tmp;
	char	*env_value;
	int		i;
	int		j;

	i = 0;
	env_value = ft_calloc(1, 1);
	while (env[i])
	{
		if (search_env(key, env, i, &j) == 0)
			break ;
		i++;
	}
	if (env[i])
	{
		free(env_value);
		env_value = ft_substr(env[i], j + 1, ft_strlen(env[i]));
	}
	if (g_exist.quote)
	{
		tmp = env_value;
		env_value = ft_strtrim(env_value, "\t ");
		free(tmp);	
	}
	return (env_value);
}

void	set_pwd_oldpwd(char *new_path, char **env, int type)
{
	int pwd;
	int oldpwd;
	int j;

	oldpwd = 0;
	while (env[oldpwd])
	{
		if (search_env("OLDPWD", env, oldpwd, &j) == 0)
			break ;
		oldpwd++;
	}
	pwd = 0;
	while (env[pwd])
	{
		if (search_env("PWD", env, pwd, &j) == 0)
			break ;
		pwd++;
	}
	// free OLDPWD
	free(env[oldpwd]);
	// point OLDPDW to PWD
	env[oldpwd] = ft_strjoin("OLDPWD=", ft_substr(env[pwd], j + 1, ft_strlen(env[pwd])));
	// set PWD to the new location
	free(env[pwd]);
	if(type == 1)
		env[pwd] = ft_strjoin("PWD=", new_path);
	else
		env[pwd] = ft_strjoin("PWD=", ft_strjoin(&env[oldpwd][7], "/."));
	// printf("Key => %s \n", key);
	// printf("New valude => %s \n", value);
	// printf("===> %s \n", env[i]);
}
