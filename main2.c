/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/25 16:00:24 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char **dup_arr1()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 3);
	arr[0] = strdup("aaaa");
	arr[1] = strdup("bbbb");
	arr[2] = NULL;

	return (arr);
}

char **dup_arr2()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 4);
	arr[0] = strdup("echo");
	arr[1] = strdup("aaaa");
	arr[2] = strdup("bbbb");
	arr[3] = NULL;
	return (arr);
}

// void set_test(t_minishell *minishell)
// {
// 	t_pipeline *pipe;
// 	t_command	*command;
// 	t_redirection	*recirection;

	
// 	recirection = malloc(sizeof(t_redirection));
// 	recirection->type = RIGHT_REDIR;
// 	recirection->file_name = strdup("file1");
// 	recirection->next = NULL;

// 	command = malloc(sizeof(t_command));
// 	command->recirections = recirection;
// 	command->cmd = strdup("echo aaaa	 bbbb");
// 	command->exec = strdup("echo");
// 	command->args = dup_arr1();
// 	command->full_args = dup_arr2();
// 	command->option = 0;
// 	command->next = NULL;
	
// 	pipe = malloc(sizeof(t_pipeline));
// 	pipe->pipe_count = 0;
// 	pipe->commands = command;
// 	pipe->next = NULL;
	
	
// 	minishell->pipes = pipe;
	
// }
void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*current;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	current = *alst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}


void set_test(t_minishell *minishell)
{
	t_list *list1, *list2, *list3;
	t_list *tmp1, *tmp2, *tmp3;
	
	t_pipeline *pipe;
	t_command	*command;
	t_redirection	*recirection;

	
	list1 = NULL;
	list2 = NULL;
	list3 = NULL;



	tmp1 = malloc(sizeof(t_list));
	tmp2 = malloc(sizeof(t_list));
	tmp3 = malloc(sizeof(t_list));

	
	recirection = malloc(sizeof(t_redirection));
	recirection->type = RIGHT_REDIR;
	recirection->file_name = strdup("file1");
	
	tmp1->content = recirection;
	tmp1->next = NULL;
	ft_lstadd_back(&list3, tmp1);

	command = malloc(sizeof(t_command));
	command->redirections = list3;
	command->cmd = strdup("echo aaaa	 bbbb");
	command->exec = strdup("echo");
	command->args = dup_arr1();
	command->full_args = dup_arr2();
	command->option = 0;

	tmp2->content = command;
	tmp2->next = NULL;
	ft_lstadd_back(&list2, tmp2);
	
	pipe = malloc(sizeof(t_pipeline));
	pipe->pipe_count = 10;
	pipe->commands = list2;

	tmp3->content = pipe;
	tmp3->next = NULL;
	ft_lstadd_back(&list1, tmp3);
	
	
	minishell->pipes = list1;
	
}




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*					 the above is just for testing							 */
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int handle_command(t_command *command)
{
	
	printf("cmd = %s \n", command->cmd);
	exit(0);
	return (1);
}


int commands_loop(t_minishell *minishell, t_list *commands)
{
   	t_list *current;
   	t_pipeline *pipe;
	int status;
	
	// handle redirections // make files // and handle file descripters

	
	
	status = 1;
	current = commands; // current =  command_0 | command | command | command | ....
   	while(current != NULL) {
		// TODO: wait until each command is executed

		// command = (t_command*)current->content;
		// printf("cmd = %s \n", current->content->cmd);
		// handle_command(current->content);
		// printf("1111");


		pipe = (t_pipeline*)commands;
		printf("%d \n", pipe->pipe_count);


		
		// status = shell_execute(current, minishell);
		// if(status == 0)
		// 	return (0);
      	current = current->next;
   	}
	return (1);
}


int pipes_loop(t_minishell *minishell)
{
   	t_list *current;
	int status;
	
	status = 1;
	current = minishell->pipes;
	
   	while(current != NULL) {
		// status =  commands_loop(minishell, current->commands); // command | command | command | command | ....
		status =  commands_loop(minishell, current->content); // command | command | command | command | ....
		if(status == 0)
			return (0);
		// printf("cmd = %s \n", current->commands->cmd);
		// printf("1111");

      	current = current->next;
   	}
	return (1);
}

int main(int argc, char **argv, char **env)
{

	t_minishell minishell;

	minishell.env = env;
	set_test(&minishell);




	// "echo aaaa	 bbbb > file1"  
	pipes_loop(&minishell);

	
	// printf("==> %s \n", minishell.pipes->commands->cmd);

	return (EXIT_SUCCESS);
}


