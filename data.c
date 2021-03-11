/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/08 17:49:34 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char **dup_arr_cd()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 3);
	arr[0] = strdup("cd");
	arr[1] = strdup("gnl");
	arr[2] = NULL;
	return (arr);
}

char **dup_arr_grep()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 3);
	arr[0] = strdup("grep");
	arr[1] = strdup("PAGER=");
	arr[2] = NULL;
	return (arr);
}

char **dup_arr_pwd()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 2);
	arr[0] = strdup("pwd");
	arr[1] = NULL;
	return (arr);
}

char **dup_arr_echo()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 4);
	arr[0] = strdup("echo");
	arr[1] = strdup("dsfdsfs sdfsfds      sdf");
	arr[2] = strdup("end");
	arr[3] = NULL;
	return (arr);
}


char **dup_arr_ls()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 2);
	arr[0] = strdup("ls");
	arr[1] = NULL;

	return (arr);
}


char **dup_arr_env()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 2);
	arr[0] = strdup("env");
	arr[1] = NULL;

	return (arr);
}


char **dup_arr_export()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 5);
	arr[0] = strdup("export");
	arr[1] = strdup("AAAAAAAAAAAAAAAAAAAAAA=aaaaaaa");
	arr[2] = strdup("BBBBBBBBBBBB=aaaaaaa");
	arr[3] = strdup("MAKELEVEL=55");
	arr[4] = NULL;

	return (arr);
}


char **dup_arr_empty_export()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 2);
	arr[0] = strdup("export");
	arr[1] = NULL;

	return (arr);
}

char **dup_arr_unset()
{
	char **arr;

	arr = (char**)malloc(sizeof(char*) * 3);
	arr[0] = strdup("unset");
	arr[1] = strdup("AAAAAAAAAAAAAAAAAAAAAA");
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
	t_list *list1, *list2, *list22, *list3, *list4, *list5;
	
	// t_pipeline *pipe, *pipe2, *pipe3, *pipe4;
	
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
	redirection->file_name = strdup("file11111");
	ft_lstadd_back(&list3, ft_lstnew(redirection));

	// redirection2 = malloc(sizeof(t_redirection));
	// redirection2->type = RIGHT_REDIR;
	// redirection2->file_name = strdup("file2");
	// ft_lstadd_back(&list3, ft_lstnew(redirection2));


	// //----

	// redirection3 = malloc(sizeof(t_redirection));
	// redirection3->type = LEFT_REDIR;
	// redirection3->file_name = strdup("file2");
	// ft_lstadd_back(&list4, ft_lstnew(redirection3));


	// ----------------------------------

	// dup_arr_cd,  dup_arr_pwd, dup_arr_echo, dup_arr_ls, dup_arr_env, dup_arr_export, dup_arr_unset, dup_arr_empty_export

	command = malloc(sizeof(t_command));
	// command->redirections = list3;
	command->redirections = NULL;
	command->full_args = dup_arr_empty_export();
	ft_lstadd_back(&list2, ft_lstnew(command));
	
	command2 = malloc(sizeof(t_command));
	// command->redirections = list3;
	command2->redirections = NULL;
	command2->full_args = dup_arr_grep();
	ft_lstadd_back(&list2, ft_lstnew(command2));
/*

	command4 = malloc(sizeof(t_command));
	// command3->redirections = list3;
	command4->redirections = NULL;
	command4->full_args = dup_arr_unset();
	ft_lstadd_back(&list5, ft_lstnew(command4));

	command3 = malloc(sizeof(t_command));
	// command3->redirections = list3;
	command3->redirections = NULL;
	command3->full_args = dup_arr_env();
	ft_lstadd_back(&list4, ft_lstnew(command3));
*/
	
	// ----------------------------------
	
	// pipe = malloc(sizeof(t_pipeline));
	// pipe->commands = list2;
	ft_lstadd_back(&list1, ft_lstnew(list2));

	// pipe2 = malloc(sizeof(t_pipeline));
	// pipe2->commands = list22;
	// ft_lstadd_back(&list1, ft_lstnew(pipe2));



	// pipe4 = malloc(sizeof(t_pipeline));
	// pipe4->commands = list5;
	// ft_lstadd_back(&list1, ft_lstnew(pipe4));

	// pipe3 = malloc(sizeof(t_pipeline));
	// pipe3->commands = list4;
	// ft_lstadd_back(&list1, ft_lstnew(pipe3));


	
	
	minishell->cmds = list1;
	
}



