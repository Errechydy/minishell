/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/01/29 15:49:00 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"











char *shell_read(void)
{

	char	*line;
	int		line_return;

	line_return = get_next_line(0, &line);
	if(line_return == -1)
	{
		ft_putstr_fd("Shell: Allocation error\n", 1);
    	exit(EXIT_FAILURE);
	}
	return (line);
}