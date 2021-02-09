/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/09 19:18:57 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo_display(char *str, int escape_n)
{
	int i;
	int quote;
	char *str2;


	if (escape_n == 1)
	{
		i = 0;
		while(str[i] != '\0')
		{
			if(str[i] == 110) // start from -n n == 110
			{
				str2 = ft_strdup(&str[++i]);
				break ;
			}
			i++;
		}
	}
	else
	{
		str2 = ft_strdup(str);
	}

	quote = 0; // ' = 1; " = 2
	// ' 39
	// " 34
	// \ 92 escape
	// $ 36

	i = 0;
	while(str2[i] != '\0')
	{
		
		// if quote == 1 ===> display every single char
		if(quote == 1)
		{
			if(str2[i] != 39)
				ft_putchar_fd(str2[i], 1);
			else
				quote = 0;
		}
		// if quote == 2 ==> display env variables when there is $ or ignore it if there are no var in the env, escape characters
		// if  \ before ' or " or $ then escape it
		else if(quote == 2)
		{
			if (str2[i] != 34)
			{
				if (str2[i] == 36)
				{
					// look for the env variable and display it if exist, if it doesn't then ignore it
				}
				else
					ft_putchar_fd(str2[i], 1);
			}
			else
				quote = 0;
		}
		// handle escapes $ and escapes 
		else
		{
			// current char is = ' OR " OR $
			if(str2[i] == 39 || str2[i] == 34 || str2[i] == 36)
			{
				if(str2[i - 1] == 92)
					ft_putchar_fd(str2[i], 1);
				else if (str2[i] == 39)
				{
					quote = 1;
				}
				else if (str2[i] == 34)
				{
					quote = 2;
				}
				else if (str2[i] == 36)
				{
					// look for the env variable and display it if exist, if it doesn't then ignore it
				}
			}
			else if (str2[i] == 32 && str2[i + 1] != 32)
			{
				ft_putchar_fd(str2[i], 1);
			}
			else if(str2[i] != 92 && str2[i] != 32) //     / and Space
			{
				ft_putchar_fd(str2[i], 1);
			}
		}

		if ((str2[i] == 39 ||  str2[i] == 34) && quote == 0)
		{
			if(str2[i] == 39)
				quote = 1;
			else
				quote = 2;
		}
		
		i++;
	}
	free(str2);
}


// void echo_display(char **str, char **args, int escape_n)
// {
// 	int i;

// 	i = 0;
// 	while(args[i] != NULL)
// 	{
// 		if(i != 0)
// 			ft_putstr_fd(" ", 1);
// 		// ft_putstr_fd(args[i], 1);
// 		echo_display_chars(args[i], escape_n);
// 		i++;
// 	}
// }

int	validate_quotes(char **str)
{
	int i;
	int j;
	int count1;
	int count2;

	count1 = 0;
	count2 = 0;
	j = 0;
	while(str[j] != NULL)
	{
		i = 0;
		while(str[j][i] != '\0')
		{
			if(str[j][i] == 34) // "
				count1++;
			else if(str[j][i] == 39) // '
				count1++;
			i++;
		}
		j++;
	}
	
	if((count1 % 2) != 0 || (count2 % 2) != 0)
		return (0);
	return (1);
}

int shell_echo(t_command *command)
{

	if(validate_quotes(command->args) == 0)
	{
		ft_putstr_fd("Shell: We haven\'t been asked to handle \' or \" for multiline commands \n", 1);
		return(1);
	}
	
	if(ft_strcmp(command->args[0], "-n") == 0)
	{
		echo_display(command->str, 1);
	}
	else
	{
		echo_display(command->str, 0);
		ft_putstr_fd("\n", 1);
	}
	return (1);
}

