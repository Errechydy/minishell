/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:17:20 by mobaz             #+#    #+#             */
/*   Updated: 2020/12/10 17:04:50 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

size_t			ft_strlen_(const char *s, int strlen_type);
char			*ft_strdup_(const char *s1);
int				new_line_exist(const char *ha);
int				join_buff(char **all_b, char *new_b, int fd);
int				set_line2(char **all_buff, int read_r, size_t	i, int fd);
int				set_line(char **all_buff, char **line, int read_r, int fd);
int				get_next_line(int fd, char **line);

#endif
