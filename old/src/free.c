/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/09 16:05:18 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_double(char **str)
{
	int		i;
	int		j;

	if(!str)
		return ;
	i = 0;
	while(str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_commands(t_minishell *minishell)
{

	struct s_command *current;
	struct s_command *tmp;
	int index;
	
	current = minishell->command;
   	while(current != NULL) {
		free(current->execter);
		if(current->str)
			free(current->str);
		free_double(current->args);
		free_double(current->full);
		tmp = current;
      	current = current->next;
		free(tmp);
   	}
	minishell->command = NULL;
}


