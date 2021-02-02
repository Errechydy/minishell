/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/02 15:33:36 by ler-rech         ###   ########.fr       */
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



typedef struct s_minishell
{
    char **command;
    char **env;
} t_minishell;


int			get_next_line(int fd, char **line);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strdup(const char *s1);
int			ft_strcmp(const char *x, const char *y);
int		    ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);


void	    free_double(char **str);
char        *found_exec(t_minishell minishell);
int         shell_export(t_minishell minishell);


char		**shell_parce(char *line);
char		*shell_read(void);
int			shell_execute(t_minishell minishell);
int			shell_launch(t_minishell minishell);

int			shell_cd(char **args);
int			shell_exit(char **args);
int			shell_echo(char **args);



// Remove it later
void		read_parced_args(char **args); 

#endif
