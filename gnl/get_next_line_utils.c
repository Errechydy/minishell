/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 09:50:41 by mobaz             #+#    #+#             */
/*   Updated: 2021/01/20 16:52:30 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t		ft_strlen_(const char *s, int strlen_type)
{
	size_t	num;
	size_t	i;

	if (s == NULL)
		return (0);
	num = 0;
	i = 0;
	if (strlen_type == 1)
		while (s[i] != '\0')
		{
			num++;
			i++;
		}
	else
		while (s[i] != '\0' && s[i] != '\n')
		{
			num++;
			i++;
		}
	return (num);
}

char		*ft_strdup_(const char *s1)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)malloc((ft_strlen_(s1, 1) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int			join_buff(char **all_b, char *new_b, int fd)
{
	size_t	i;
	size_t	j;
	char	*temp;

	if (!(temp = malloc((ft_strlen_(all_b[fd], 1) + ft_strlen_(new_b, 1) + 1))))
		return (0);
	j = 0;
	i = -1;
	if (all_b[fd])
		while (*(all_b[fd] + ++i) != '\0')
			temp[j++] = *(all_b[fd] + i);
	i = 0;
	if (new_b)
		while (new_b[i] != '\0')
			temp[j++] = new_b[i++];
	temp[j] = '\0';
	if (all_b[fd])
		free(all_b[fd]);
	if ((all_b[fd] = ft_strdup_(temp)) == 0)
	{
		free(temp);
		return (0);
	}
	free(temp);
	return (1);
}

int			set_line2(char **all_buff, int read_r, size_t i, int fd)
{
	char	*all_buff_tmp;

	if (*(all_buff[fd] + i) != '\0')
	{
		if ((all_buff_tmp = ft_strdup_(all_buff[fd] + ++i)) == 0)
			return (0);
	}
	else if (!(all_buff_tmp = ft_strdup_("")))
		return (0);
	free(all_buff[fd]);
	if (read_r)
	{
		if ((all_buff[fd] = ft_strdup_(all_buff_tmp)) == 0)
		{
			free(all_buff_tmp);
			return (0);
		}
	}
	else if ((all_buff[fd] = ft_strdup_("")) == 0)
	{
		free(all_buff_tmp);
		return (0);
	}
	free(all_buff_tmp);
	return (1);
}

int			set_line(char **all_buff, char **line, int read_r, int fd)
{
	size_t	i;

	*line = malloc((ft_strlen_(all_buff[fd], 2) + 1) * sizeof(char));
	if (*line == NULL)
		return (0);
	i = 0;
	if (all_buff[fd])
		while (*(all_buff[fd] + i) != '\0' && *(all_buff[fd] + i) != '\n')
		{
			*(*line + i) = *(all_buff[fd] + i);
			i++;
		}
	*(*line + i) = '\0';
	return (set_line2(all_buff, read_r, i, fd));
}
