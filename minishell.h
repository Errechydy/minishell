/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/09 19:09:30 by ler-rech         ###   ########.fr       */
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


#define LINE_BUFFER_SIZE 1024
# define EXIT_SUCCESS		0
# define EXIT_FAILURE		1

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"


typedef struct	s_command
{
	char			    *execter;
	char			    **args;
	char			    **full;
	char			    *str;
	int 			    key;
	struct s_command	*next;
}				t_command;

typedef struct s_minishell
{
    struct s_command    *command;
    char                **env;
} t_minishell;



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
void		echo_display(char *str, int escape_n);


void		shell_parce(t_minishell *minishell, char *line);
char		*shell_read(void);
int			shell_execute(t_command *current, t_minishell *minishell);
int 		shell_launch(t_command *command, t_minishell *minishell);

int			shell_cd(t_command *command);
int			shell_exit(t_command *command);
int			shell_echo(t_command *command);



// Remove it later
void        read_parced_args(t_minishell *minishell);

#endif
