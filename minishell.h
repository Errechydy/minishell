/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/23 18:31:45 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <sys/stat.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>
#include <sys/errno.h>
# include "gnl/get_next_line.h"


# define EXIT_SUCCESS		0
# define EXIT_FAILURE		1


# define LEFT_REDIR 1
# define RIGHT_REDIR 2
# define DRIGHT_REDIR 3




typedef struct	s_list
{
	void					*content;
	struct s_list			*next;
}				t_list;


typedef struct  s_redirection
{
	int						type;		   // 1 = > , 2 = >>, 3 = <
	char					*file_name;
}			   t_redirection;

typedef struct  s_command
{
	char					*cmd;		   // "echo aaaa	 bbbb" // don't include -n
	char					*exec;		  // "echo"
	char					**args;		 // ["aaaa", "bbbb"]
	char					**full_args;	// ["echo", "aaaa", "bbbb"]
	int						option;		 // 1 if echo -n, 0 if not
	t_list					*redirections;
}			   t_command;

typedef struct	s_pipeline // command | command | command |
{
	int						pipe_count;
	t_list					*commands;
}				t_pipeline;

typedef struct	s_minishell // pipes ; pipes ; pipes
{
	t_list					*pipes;
	char					**env;
}				t_minishell;





// t_list list;

// WHile (list)
// {
// 	t_command cmd = (t_command)list.content
// }

// while()














int			get_next_line(int fd, char **line);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strdup(const char *s1);
int			ft_strcmp(const char *x, const char *y);
int		    ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putchar_fd(char c, int fd);
int			ft_isalpha(int c);
char 		*trimit(char *s);
size_t		ft_strlen(const char *s);

int			env_compair(char *var1, char *var2);
int			vars_counter_and_update(char **new_vars, char **env);
int			var_exist(char *var, char **env);
char		**get_new_env(char **new_vars, char **env, int len);
int			ft_is_equal(int c);
int			arg_has_equal(char *str);
int			ft_is_userscore(int c);
int			arg_start_with_char(char *str);
int 		is_valid_arg(char *arg, int show_error);
int 		is_valid_arg2(char *arg, int show_error);
int			count_valid_args(char **args);
void		set_valid_envs(t_command *command);

void	    free_double(char **str);
void        free_commands(t_minishell *minishell);

int         shell_env(t_minishell *minishell);
int			shell_export(t_command *command, t_minishell *minishell);
int			shell_unset(t_command *command, t_minishell *minishell);
int			set_env(t_minishell *minishell, char **env);
int			words_counter(char **env);
char		*found_exec(t_command *command, t_minishell *minishell);
void		echo_display(char *str, int escape_n, t_minishell *minishell);


void		shell_parce(t_minishell *minishell, char *line);
char		*shell_read(void);
int			shell_execute(t_command *current, t_minishell *minishell);
int 		shell_launch(t_command *command, t_minishell *minishell);

int			shell_cd(t_command *command);
int			shell_exit(t_command *command);
int			shell_echo(t_command *command, t_minishell *minishell);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *));













// int 			handle_redirections(t_minishell *minishell, t_redirection *redirection);
int 			loop_redirections(t_minishell *minishell, t_command *command);
int 			handle_command(t_minishell *minishell, t_command *command);
int 			commands_loop(t_minishell *minishell, t_pipeline *pipe);
int 			pipes_loop(t_minishell *minishell);







// Remove it later
void        read_parced_args(t_minishell *minishell);

#endif
