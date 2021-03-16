/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/16 17:28:28 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ex_helper1(char *arg)
{
	ft_putstr_fd("shell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exist.last_exec = 1;
	return (0);
}

void	ex_helper2(char **env)
{
	int j;

	j = 0;
	while (env[j] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		display_env_chars(env[j]);
		ft_putchar_fd('\n', 1);
		j++;
	}
}
