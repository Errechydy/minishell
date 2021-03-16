/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/16 18:00:15 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int valid_arg(char *str)// 1 : error (not valid arg)
{
	int i;

	if(ft_isdigit(str[0]) == 1)
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

int		shell_unset(t_command *command, t_minishell *minishell)
{
	int i;

	i = 0;
	while (command->full_args[i] != NULL)
	{
		if(valid_arg(command->full_args[i]) == 1)
			printf("---- NOT valid\n");
		else
			printf("++++Valid\n");
		i++;
	}
	
	
	return (1);
}
