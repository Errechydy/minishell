/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/28 15:24:01 by ler-rech         ###   ########.fr       */
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

t_list		*ft_lstnew(void *content)
{
	t_list	*list_elem;

	list_elem = malloc(sizeof(t_list));
	if (list_elem == NULL)
		return (NULL);
	list_elem->content = content;
	list_elem->next = NULL;
	return (list_elem);
}


void set_test(t_minishell *minishell)
{
	t_list *list1, *list2, *list3, *list4;
	
	t_pipeline *pipe;
	
	t_command	*command;
	
	t_redirection	*redirection;
	t_redirection	*redirection2;
	t_redirection	*redirection3;

	
	list1 = NULL;
	list2 = NULL;
	list3 = NULL;
	list4 = NULL;

	
	redirection = malloc(sizeof(t_redirection));
	redirection->type = RIGHT_REDIR;
	redirection->file_name = strdup("file1");
	ft_lstadd_back(&list3, ft_lstnew(redirection));

	redirection2 = malloc(sizeof(t_redirection));
	redirection2->type = RIGHT_REDIR;
	redirection2->file_name = strdup("file2");
	ft_lstadd_back(&list3, ft_lstnew(redirection2));


	
	// ----------------------------------

	command = malloc(sizeof(t_command));
	command->redirections = list3;
	command->cmd = strdup("echo aaaa	 bbbb");
	command->exec = strdup("echo");
	command->args = dup_arr1();
	command->full_args = dup_arr2();
	command->option = 0;
	ft_lstadd_back(&list2, ft_lstnew(command));
	
	pipe = malloc(sizeof(t_pipeline));
	pipe->pipe_count = 10;
	pipe->commands = list2;
	ft_lstadd_back(&list1, ft_lstnew(pipe));
	
	
	minishell->pipes = list1;
	
}




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*					 the above is just for testing							 */
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*
int handle_redirections(t_minishell *minishell, t_redirection *redirection)
{
	int status;
	// if << filename , filename doesn't exist return 0;
	// change fd (to the last file) 
	printf("cmd = %s \n", redirection->file_name);
	// exit(0);
	return (1);
}
int loop_redirections(t_minishell *minishell, t_command *command)
{
	
	t_list *current;
	int status;
	
	status = 1;
	current = command->redirections; // current =  command_0 | command | command | command | ....
   	while(current != NULL) {
		status = handle_redirections(minishell, (t_redirection*)current->content);
		if(status == 0)
			return (0);

		if(current->next == NULL)
		{
			printf("reached the last element \n");
		}
		
      	current = current->next;
		
   	}
	return (1);
}
*/

int	read_file(char* file_name)
{
	int fd;
    fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("Minishell: %s: No such file or directory", file_name);
		return (-1);
	}
	return (fd);
}

int	create_empty_file(char* file_name)
{
	int fd;
    fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT | S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR, 0644);
	if (fd < 0)
	{
		printf("Minishell: %s: Couldn't create the file", file_name);
		return (-1);
	}
	return (fd);
}


int loop_redirections(t_minishell *minishell, t_command *command)
{
	
	t_list *current;
	t_redirection *redirection;
	int status;
	int	fd;
	
	status = 1;
	current = command->redirections; 									// current =  redirection | redirection | redirection | redirection | ....

   	while(current != NULL) {

		redirection = (t_redirection*)current->content;
		if(redirection->type == 1) 										// read from file (STDIN)
		{
			fd = read_file(redirection->file_name);
			if (fd < 0)
				return (0);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else 															// Write to a file (STDOUT)
		{
			if(redirection->type == 2)
				fd = create_empty_file(redirection->file_name);
			else
				fd = create_empty_file(redirection->file_name);			 // append to file
			if (fd < 0)
				return (0);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
      	current = current->next;
		
   	}
	return (1);
}


int handle_command(t_minishell *minishell, t_command *command)  // current =  command_0 | command | command | command | ....
{
	int status;
	int fid;

	fid = fork();
	if(fid < 0)
	{
		printf("Minishell: Couldn't fork process");
		return (0);
	}
	else if(fid == 0) // Child process
	{
		// handle redirections // make files // and handle file descripters
		status = loop_redirections(minishell, command);
		if(status == 0)
			return (0);
		
		printf("cmd = %s \n", command->cmd);


		// status = shell_execute(current, minishell);
		// if(status == 0)
		// 	return (0);
	}
	else // Parent process
	{
		wait(NULL);
		// get any error from child process and display it
		
		printf("cmd2 = %s \n", command->cmd);
	}
	


	return (1);
}












int commands_loop(t_minishell *minishell, t_pipeline *pipe)
{
   	t_list *current;
	int status;
	
	status = 1;
	current = pipe->commands; // current = {command_0 | command | command | command | .... }
   	while(current != NULL) {

		   
		status = handle_command(minishell, (t_command*)current->content); // command_0
		if(status == 0)
			return (0);
      	current = current->next;

		  
   	}
	return (1);
}


int pipes_loop(t_minishell *minishell)
{
   	t_list *current;
	int status;
   	t_pipeline *pipe;
	
	status = 1;
	current = minishell->pipes;
   	while(current != NULL) {
		status =  commands_loop(minishell, (t_pipeline*)current->content); // pipe | pipe | pipe | pipe | ....
		if(status == 0)
			return (0);
      	current = current->next;
   	}
	return (1);
}

int main(int argc, char **argv, char **env)
{

	t_minishell minishell;

	minishell.env = env;
	set_test(&minishell);

	pipes_loop(&minishell);

	

	return (EXIT_SUCCESS);
}


