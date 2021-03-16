/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/16 17:34:59 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_valid_arg(char *arg, int show_error)
{
	char	**str;

	if (arg[0] == '=' && show_error == 1)
		return (ex_helper1(arg));
	str = ft_split(arg, '=');
	if (arg_start_with_char(str[0]) == 0)
	{
		free_double(str);
		return (1);
	}
	else
	{
		if (show_error == 1)
		{
			ft_putstr_fd("shell: export: '", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_exist.last_exec = 1;
		}
		free_double(str);
		return (0);
	}
	free_double(str);
	return (0);
}

int		display_env_ordred(char **env)
{
	char	*temp;
	int		count;
	int		i;
	int		j;

	count = words_counter(env);
	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	ex_helper2(env);
	return (0);
}

void	ex_helper3(t_minishell *minishell, char **interm,
	int new_vars, int env_len)
{
	char	**env_tmp;
	char	**new_env;
	int		i;
	int		j;

	new_env = get_new_env(interm, minishell->env, new_vars);
	env_tmp = (char **)malloc(sizeof(char *) * (env_len + new_vars + 1));
	i = 0;
	while (minishell->env[i] != NULL)
	{
		env_tmp[i] = ft_strdup(minishell->env[i]);
		i++;
	}
	j = 0;
	while (new_env[j] != NULL)
	{
		env_tmp[i] = ft_strdup(new_env[j]);
		j++;
		i++;
	}
	env_tmp[i] = NULL;
	free_double(new_env);
	free_double(minishell->env);
	free_double(interm);
	minishell->env = env_tmp;
}

int		shell_export(t_command *command, t_minishell *minishell)
{
	int		env_len;
	int		new_vars;
	char	**interm;

	if (command->full_args[1] == NULL)
	{
		display_env_ordred(minishell->env);
		return (1);
	}
	interm = set_valid_envs(command);
	new_vars = vars_counter_and_update(interm, minishell->env);
	env_len = words_counter(minishell->env);
	ex_helper3(minishell, interm, new_vars, env_len);
	return (1);
}
