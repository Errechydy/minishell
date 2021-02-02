/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/01/26 18:01:42 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"











/*
void shell_loop(t_minishell minishell)
{
  char *line;
  char **args;
  int status;
  
  status = 1;
  while (status)
  {
		ft_putstr_fd("===> ", 1);
		line = shell_read();
		if(line[0] != '\0')
		{
			args = shell_parce(line); // lsh_split_line
			read_parced_args(args);
			// status = shell_execute(args);
			free(args);
			// printf("%s\n", line);
		}
		free(line);
  };
}

*/
void shell_loop(t_minishell minishell)
{
	
  char *line;
  int status;
  
  status = 1;
  while (status)
  {
		ft_putstr_fd("===> ", 1);
		line = shell_read();
		if(line[0] != '\0')
		{
			minishell.command = shell_parce(line); // lsh_split_line
			// read_parced_args(minishell.command);
			status = shell_execute(minishell);
			free(minishell.command);
			// printf("%s\n", line);
		}
		free(line);
  };
  
}

int main(int argc, char **argv, char **env)
{
	// Load config files, if any.
	t_minishell minishell;

	// Run command loop.
	minishell.env = env;
	shell_loop(minishell);
	// shell_loop(env);


	// Perform any shutdown/cleanup.





	// int i;

	// i = 0;
	// while(env[i] != NULL)
	// {
	// 	printf("---> %s \n", env[i]);
	// 	i++;
	// }


	return (EXIT_SUCCESS);
}
