/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/09 19:11:20 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*s12(char *cmnd)
{
	int i;
	char *str;
	int	first_char;

	first_char = 0;
	i = 0;
	while(cmnd[i] != '\0')
	{
		if(cmnd[i] >= 33)
			first_char = 1;
		if(cmnd[i] == 32 && first_char == 1)
			return (ft_strdup(&cmnd[i]));
		i++;
	}
	return (NULL);
}


void insert_command(t_minishell *minishell, int index, char *cmnd)
{
	int i;
	char **tokens;
	struct s_command *new;
	struct s_command *current;
	int len;
	
	tokens = ft_split(cmnd, ' ');
	len = words_counter(tokens);
	new = (struct s_command*) malloc(sizeof(struct s_command));
	new->args = malloc(sizeof(char*) * len);
	i = 1;
	while(tokens[i] != NULL)
	{
		new->args[i - 1] = ft_strdup(tokens[i]); 
		i++;
	}
	new->args[i - 1] = NULL;
	new->key = index;
	new->full = tokens;
	new->next = NULL; 
	new->execter = ft_strdup(tokens[0]);
	// new->str = args_as_str(cmnd);
	new->str = ft_strdup(trimit(s12(cmnd)));

	current = minishell->command;
	
	// while(current != NULL) {
	while(current != NULL && current->next != NULL) {
        current = current->next;
   	}
	if(minishell->command == NULL)
		minishell->command = new;
	else
		current->next = new;
	// free_double(tokens);
}

void	shell_parce(t_minishell *minishell, char *line)
{
	int i;
	char **commands;

	commands = ft_split(line, ';');
	i = 0;
	while(commands[i] != NULL)
	{
		insert_command(minishell, i, commands[i]);
		i++;
	}

}

