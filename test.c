/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/03 18:15:09 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"



void read_parced_args(t_minishell *minishell)
{

   	struct s_command *current;
	int index;
	
	current = minishell->command;
   	while(current != NULL) {
      	printf("key : %d   ,    executer : %s        ,      ", current->key, current->execter);
		index = 0;
	  	while(current->args[index] != NULL)
		{
			printf("arg[%d] : %s  ,    ", index, current->args[index]);
			index++;
		}
		printf("\n");
      	current = current->next;
   	}
}