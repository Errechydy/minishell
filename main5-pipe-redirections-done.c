/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main5-pipe-redirections-done.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/28 16:55:04 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char **dup_arr1()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 1);
	arr[0] = NULL;

	return (arr);
}

char **dup_arr2()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 2);
	arr[0] = strdup("ls");
	arr[1] = NULL;
	return (arr);
}


char **dup_arr3()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 2);
	arr[0] = strdup("main");
	arr[1] = NULL;

	return (arr);
}

char **dup_arr4()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 3);
	arr[0] = strdup("/usr/bin/grep");
	arr[1] = strdup("main");
	arr[2] = NULL;
	return (arr);
}

char **dup_arr5()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 2);
	arr[0] = strdup("main2");
	arr[1] = NULL;

	return (arr);
}

char **dup_arr6()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 3);
	arr[0] = strdup("/usr/bin/grep");
	arr[1] = strdup("main2");
	arr[2] = NULL;
	return (arr);
}


char **dup_arr7()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 2);
	arr[0] = strdup("main2.k");
	arr[1] = NULL;

	return (arr);
}

char **dup_arr8()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 3);
	arr[0] = strdup("/usr/bin/grep");
	arr[1] = strdup("main2.k");
	arr[2] = NULL;
	return (arr);
}













/*-----------------------------------------------*/
/*-----------------------------------------------*/


int		ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
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

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*					 the above is just for testing							 */
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////




void set_test(t_minishell *minishell)
{
	t_list *list1, *list2, *list3, *list4;
	
	t_pipeline *pipe;
	
	t_command	*command;
	t_command	*command2;
	t_command	*command3;
	t_command	*command4;
	
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


	//----

	redirection3 = malloc(sizeof(t_redirection));
	redirection3->type = LEFT_REDIR;
	redirection3->file_name = strdup("file2");
	ft_lstadd_back(&list4, ft_lstnew(redirection3));


	// ----------------------------------

	command = malloc(sizeof(t_command));
	command->redirections = list3;
	// command->redirections = NULL;
	command->cmd = strdup("/bin/ls");
	command->exec = strdup("/bin/ls");
	command->args = dup_arr1();
	command->full_args = dup_arr2();
	command->option = 0;
	ft_lstadd_back(&list2, ft_lstnew(command));




	command2 = malloc(sizeof(t_command));
	command2->redirections = list4;
	command2->cmd = strdup("/usr/bin/grep main");
	command2->exec = strdup("/usr/bin/grep");
	command2->args = dup_arr3();
	command2->full_args = dup_arr4();
	command2->option = 0;
	ft_lstadd_back(&list2, ft_lstnew(command2));


	command3 = malloc(sizeof(t_command));
	command3->redirections = NULL;
	command3->cmd = strdup("/usr/bin/grep main2");
	command3->exec = strdup("/usr/bin/grep");
	command3->args = dup_arr5();
	command3->full_args = dup_arr6();
	command3->option = 0;
	ft_lstadd_back(&list2, ft_lstnew(command3));


	command4 = malloc(sizeof(t_command));
	command4->redirections = NULL;
	command4->cmd = strdup("/usr/bin/grep main2.k");
	command4->exec = strdup("/usr/bin/grep");
	command4->args = dup_arr7();
	command4->full_args = dup_arr8();
	command4->option = 0;
	ft_lstadd_back(&list2, ft_lstnew(command4));

	
	
	// ----------------------------------
	
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



int commands_loop(t_minishell *minishell, t_pipeline *my_pipe)
{
   	t_list *current;
	int status;
	t_command *command;


	int commands_len = ft_lstsize(my_pipe->commands);
	int **pipes_fd;
	int *forks;
	
	forks = malloc((commands_len + 1) * (sizeof(int*)));
	pipes_fd = malloc(commands_len * (sizeof(int*)));

	int j = 0;
	while (j < (commands_len - 1))
	{
		pipes_fd[j] = malloc(2 * sizeof(int));
		
		if (pipe(pipes_fd[j]) == -1)
		{
			return (1);
		}
		j++;
	}
	
	status = 1;
	current = my_pipe->commands; // current = {command_0 | command | command | command | .... }
	int i = 0;
	int f = 0;

   	while(current != NULL)
	{
		command = (t_command*)current->content;
		

		forks[i] = fork();
		if (forks[i] < 0)
		{
			return (2);
		}
		if (forks[i] == 0)
		{
			// Child process 
			if (i == 0) // first fork
			{
				dup2(pipes_fd[0][1], 1);
			}
			else if (i == (commands_len - 1)) // last fork
			{
				dup2(pipes_fd[i - 1][0], 0);
			}
			else
			{
				dup2(pipes_fd[i - 1][0], 0);
				dup2(pipes_fd[i][1], 1);
			}
			// close all pipes_fd
			f = 0;
			while (f < (commands_len - 1))
			{
				close(pipes_fd[f][0]);
				close(pipes_fd[f][1]);
				f++;
			}
			// handle redirections
			status = loop_redirections(minishell, command);
			if(status == 0)
				return (0);
			
			execve(command->exec, command->full_args, minishell->env);
			
			exit(0);
		}
		
		i++;
      	current = current->next;
   	}
	f = 0;
	while (f < (commands_len - 1))
	{
		close(pipes_fd[f][0]);
		close(pipes_fd[f][1]);
		f++;
	}
	f = 0;
	while (f < commands_len)
	{
		waitpid(forks[f], NULL, 0);
		f++;
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


