/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/06 17:05:28 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int env_compair(char *var1, char *var2)
{
	int		res;
	char	**str1;
	char	**str2;
	
	res = 0;
	str1 = ft_split(var1, '=');
	str2 = ft_split(var2, '=');
	if (ft_strcmp(str1[0], str2[0]) == 0)
	{
		// printf("%s == %s \n", str1[0], str1[0]);
		res = 1;
	}
	free_double(str1);
	free_double(str2);
	return (res);
}

int vars_counter_and_(char **new_vars, char **env)
{
	int i;
	int j;
	int counter;

	counter = 0;
	i = 0;
	while (new_vars[i] != NULL)
	{
		j = 0;
		while (env[j] != NULL)
		{
			if(env_compair(new_vars[i], env[j]) == 1)
			{
				// 
				// free(env[j]);
				// env[j] = ft_strdup(new_vars[i]);
				
				counter++;
			}
			j++;
		}
		i++;
	}
	// counter = words_counter(new_vars) - counter;
	return (counter);
}

int	var_exist(char *var, char **env)
{
	int j;

	j = 0;
	while (env[j] != NULL)
	{
		if(env_compair(var, env[j]) == 1)
			return (1);
		j++;
	}
	return (0);
}

char	**get_new_env(char **new_vars, char **env, int len)
{
	int i;
	int j;
	char **new_env;

	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	j = 0;
	while (new_vars[i] != NULL)
	{
		if(var_exist(new_vars[i], env) == 0)
		{
			new_env[j] = ft_strdup(new_vars[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	ft_is_equal(int c)
{
	if (c == 61)
		return (1);
	else
		return (0);
}

int		arg_has_equal(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_is_equal(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int		ft_is_userscore(int c)
{
	if(c == 95)
		return (1);
	return (0);
}

int		arg_start_with_char(char *str)
{
	if(ft_isalpha(str[0]) || ft_is_userscore(str[0]))
		return (1);
	return (0);
}

int is_valid_arg(char *arg, int show_error, char *str)
{
	// if arg has at least one "=", don't show error in this case
	if(arg_has_equal(arg) == 1) // TODO: crate this
	{
		// else if (it starts with something other than char), show error
		if(arg_start_with_char(arg) == 1) // TODO: crate this
		{
			return (1);
		}
		else
		{
			// if show_error == 1 ===> show errors
			if(show_error == 1)
			{
				ft_putstr_fd("shell: ", 1);
				ft_putstr_fd(str, 1);
				ft_putstr_fd(": `", 1);
				ft_putstr_fd(arg, 1);
				ft_putstr_fd("': not a valid identifier\n", 1);
			}
			return (0);
		}
	}
	return (0);
}



void set_valid_envs2(t_command *command)
{
	int i;
	int j;
	char **new_env;
	int len;

	len = count_valid_args(command->args);
	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	j = 0;
	while (command->args[i] != NULL)
	{
		if(is_valid_arg(command->args[i], 1, "unset") == 1)
		{
			new_env[j] = ft_strdup(command->args[i]);
			j++;
		}
		
		i++;
	}
	new_env[j] = NULL;
	free_double(command->args);
	command->args = new_env;
}


int		keep_env(char *arg, char **args)
{
	int i;

	i = 0;
	while (args[i] != NULL)
	{
		if(env_compair(args[i], arg) == 0)
			return (0);
		i++;
	}
	return (1);
}

int shell_unset(t_command *command, t_minishell *minishell)
{

// TODO: export many variables exm: export A=123 B=345 .....
// TODO: check if they don't start with a number
// TODO: chat they have '=' without spaces
// TODO: if the variable already exist then upadate it


	
	char **env_tmp;
	int env_len;
	int i;
	int new_vars;
	int j;
	char **new_env;

	set_valid_envs2(command); // command->args // has valid arguments now
	

	new_vars = vars_counter_(command->args, minishell->env); // argsNum that needs to be unset


	
	env_len = words_counter(minishell->env);
	env_tmp = (char **)malloc(sizeof(char *) * (env_len - new_vars + 1));

	
	i = 0;
	while(minishell->env[i] != NULL)
	{
		if(keep_env(minishell->env[i], command->args) == 1)
			env_tmp[i] = ft_strdup(minishell->env[i]);
		i++;
	}

	env_tmp[i] = NULL;

	
	free_double(new_env);
	free_double(minishell->env);
	minishell->env = env_tmp;
	return (1);
}
