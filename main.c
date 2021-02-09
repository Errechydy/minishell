/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/09 19:06:52 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"


// int wait_command(t_command *command, t_minishell *minishell)
// {
// 	pid_t pid = fork();
//     if (pid == 0) {
//         printf("HC: hello from child\n");
//         exit(17);
//     } else {
//         int child_status;
//         printf("HP: hello from parent\n");
//         waitpid(pid, &child_status, 0); // Waits for child to end
//         printf("CT: child result %d\n", WEXITSTATUS(child_status));
//     }
//     printf("Bye\n");
//     return 0;
// }

int commands_loop(t_minishell *minishell)
{
   	struct s_command *current;
	int index;
	int status;
	
	status = 1;
	current = minishell->command;
   	while(current != NULL) {
		// TODO: wait until each command is executed
		status = shell_execute(current, minishell);
		if(status == 0)
			return (0);
      	current = current->next;
   	}
	return (1);
}

int shell_execute(t_command *command, t_minishell *minishell)
{
	// printf("---> %s\n", command->str);
	if(strcmp(command->execter, "cd") == 0)
		return (shell_cd(command));
	else if (strcmp(command->execter, "echo") == 0)
		return (shell_echo(command));
	else if (strcmp(command->execter, "exit") == 0)
		return (shell_exit(command));
	else if (strcmp(command->execter, "export") == 0)
		return (shell_export(command, minishell));
	else if (strcmp(command->execter, "unset") == 0)
		return (shell_unset(command, minishell));
	else if (strcmp(command->execter, "env") == 0)
		return (shell_env(minishell));
	return shell_launch(command, minishell);
}

void shell_loop(t_minishell *minishell)
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
			// minishell->command = shell_parce(minishell, line);
			shell_parce(minishell, line);
			// read_parced_args(minishell);
			status = commands_loop(minishell);
			// status = shell_execute(minishell);
			free_commands(minishell);
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
	if(set_env(&minishell, env) == 0)
		return(EXIT_FAILURE);
	minishell.command = NULL;
	shell_loop(&minishell);


	// Perform any shutdown/cleanup.





	// int i;

	// i = 0;
	// while(env[i] != NULL)
	// {
	// 	printf("---> %s \n", env[i]);
	// 	i++;
	// }

	free_double(minishell.env);

	return (EXIT_SUCCESS);
}


