/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:17:20 by mobaz             #+#    #+#             */
/*   Updated: 2021/01/20 16:52:37 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					new_line_exist(const char *ha)
{
	if (!ha)
		return (0);
	while (*ha != '\0')
	{
		if (*ha == '\n')
			return (1);
		ha++;
	}
	return (0);
}

int					short_func(char **all_buff, char **line, int read_r, int fd)
{
	if (!set_line(all_buff, line, read_r, fd))
	{
		if (all_buff[fd] != NULL)
			free(all_buff[fd]);
		if (*line != NULL)
			free(*line);
		*line = NULL;
		return (-1);
	}
	if (read_r == 0)
	{
		free(all_buff[fd]);
		all_buff[fd] = NULL;
		return (0);
	}
	return (1);
}

int					get_next_line(int fd, char **line)
{
	size_t			read_r;
	char			*buff;
	static char		*all_buff[2048];

	if (fd < 0 || !line || read(fd, NULL, 0) != 0 || BUFFER_SIZE < 0
		|| !(buff = malloc((BUFFER_SIZE + 1))))
		return (-1);
	read_r = 1;
	while (!new_line_exist(all_buff[fd]))
	{
		read_r = read(fd, buff, BUFFER_SIZE);
		buff[read_r] = '\0';
		if (join_buff(all_buff, buff, fd) == 0)
		{
			free(buff);
			return (-1);
		}
		if (read_r == 0)
			break ;
	}
	free(buff);
	return (short_func(all_buff, line, read_r, fd));
}
