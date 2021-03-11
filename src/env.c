/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/10 15:16:13 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int shell_env(t_minishell *minishell)
{

	int i;
	
	i = 0;
	while(minishell->env[i] != NULL)
	{
		ft_putstr_fd(minishell->env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
    g_last_exec = 0;
	return (1);
}


/*
int set_env(t_minishell *minishell, char **env)
{

	int i;
	char **env_tmp;
	int env_len;

	env_len = words_counter(env);
	minishell->env = (char **)malloc(sizeof(char *) * (env_len + 1));
	if(minishell->env == NULL)
	{
		ft_putstr_fd("Shell: allocation error \n", 2); 
		return (0);		
	}
	i = 0;
	while(env[i] != NULL)
	{
		minishell->env[i] = ft_strdup(env[i]);
		i++;
	}
	minishell->env[i] = NULL;
	return (1);
}
*/
