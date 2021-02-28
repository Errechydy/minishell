/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:55:54 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/09 19:28:00 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int is_space(char c)
{
    if (c == 32)
		return (1);
	else
		return (0);
}

char *ltrim(char *s)
{
    while(is_space(*s) == 1) s++;
    return s;
}

char *rtrim(char *s)
{
	int len;

	len = ft_strlen(s) - 1;
	while (is_space(s[len]) == 1)
		len--;
	s[len + 1] = '\0';
	return (s);
}

char *trimit(char *s)
{
	if(!s)
		return (NULL);
    return rtrim(ltrim(s)); 
}