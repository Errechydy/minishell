/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/10 19:22:58 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		print_env_var(char *var)
{
	int i;

	i = 0;
	while (var[i] != 61)
		i++;
	ft_putstr_fd(&var[++i], 1);
}

void return_env_var(t_minishell *minishell, char *str)
{
	int i;
	
	// ft_putstr_fd("FOUND0", 1);
	// ft_putstr_fd(str, 1);
	// ft_putstr_fd("\n", 1);
	
	i = 0;
	while(minishell->env[i] != NULL)
	{
		if(env_compair(minishell->env[i], str) == 1)
		{
			// ft_putstr_fd("FOUND1", 1);
			print_env_var(minishell->env[i]);
			break ;
		}
		i++;
	}
}

int echo_env(char *str, t_minishell *minishell)
{
	int len;
	char **tmp;


	// ' 39
	// " 34
	// \ 92 escape
	// $ 36
	// space 32
	
	// ft_putstr_fd("\n", 1);
	// ft_putstr_fd("str =|", 1);
	// ft_putstr_fd(str, 1);
	// ft_putstr_fd("|\n", 1);


	tmp = ft_split(str, ' ');
	

	len = ft_strlen(tmp[0]);
	if (tmp[0][len - 1] == 34)
	{
		tmp[0][len - 1] = '\0';
	}
	

	// ft_putstr_fd("\n", 1);
	// ft_putstr_fd("tmp[0] =|", 1);
	// ft_putstr_fd(tmp[0], 1);
	// ft_putstr_fd("|\n", 1);
	

	
	
	if (tmp[0][1] == '\0')
	{
		ft_putchar_fd('$', 1);
		return (0);
	}
	else
		return_env_var(minishell, &tmp[0][1]);

	
	free_double(tmp);
	return (len);
}

int		handle_envs(char *str, int i, t_minishell *minishell)
{
	// ' 39
	// " 34
	// \ 92 escape
	// $ 36
	// space 32
	if (str[i] == 36 && (i == 0 || (i > 0 && (str[i - 1] == 32 || str[i - 1] == 34) && str[i - 1] != 92))) // == $
	{
		return (echo_env(&str[i], minishell) - 1); // this func will display the env var if exist and return the lenght from & to the first space
	}
	else if (str[i] == 92 && (str[i + 1] == 34 || str[i + 1] == 36)) // == / and i + 1 == " or $ 
	{
		// ignore it
	}
	else if (str[i] == 34)
	{
		/* code */
	}
	else
		ft_putchar_fd(str[i], 1);
	return (0);
}


void echo_display(char *str, int escape_n, t_minishell *minishell)
{
	int i;
	int quote;
	char *str2;
	int escape;

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
	escape = 0;
	// ' 39
	// " 34
	// \ 92 escape
	// $ 36
	// space 32
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
		else if(quote == 2)
		{
			if (str2[i] == 34) // == "
			{
				if(i > 0 && str2[i - 1] == 92)
				{
					ft_putchar_fd(str2[i], 1);
				}
				else
					quote = 0;
			}
			else
			{
				if (str2[i] == 36 && (str2[i - 1] == 32 || str2[i - 1] == 34) && str2[i - 1] != 92) // == $
				{

					// TODO: look for the env variable and display it if exist, if it doesn't then ignore it
					i += echo_env(&str2[i], minishell); // this func will display the env var if exist and return the lenght from & to the first space


				}
				else if (str2[i] == 92 && (str2[i + 1] == 34 || str2[i + 1] == 36)) // == / and i + 1 == " or $ 
				{
					// ignore it
				}
				else
					ft_putchar_fd(str2[i], 1);
				
				// i += handle_envs(str2, i, minishell);
			}
		}
		else
		{
			if ((i == 0 && str2[i] == 32) || (i > 0 && str2[i] == 32 && str2[i - 1] == 32)) // space
			{
				// ignore
			}
			else if (str2[i] == 36 && (str2[i + 1] == 32 || str2[i + 1] == '\0'))
			{
				ft_putchar_fd(str2[i], 1);
			}
			else
			{
				i += handle_envs(str2, i, minishell);
				
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

int	validate_quotes(char *str)
{
	int i;
	int j;
	int count1;
	int count2;
	int quote1;
	int quote2;

	quote1 = 0;
	quote2 = 0;
	count1 = 0;
	count2 = 0;
	i = 0;
	// ' 39
	// " 34
	// \ 92 escape
	// $ 36
	while(str[i] != '\0')
	{
		
		if(str[i] == 39) // '
		{
			if (!(i != 0 && quote2 == 1 && str[i - 1] == 92))
			{
				count1++;
				if (quote1 == 0)
					quote1 = 1;
				else
					quote1 = 0;
			}
		}
		else if (str[i] == 34 && quote1 == 0) // "
		{
			if(i == 0)
				count2++;
			else if (str[i - 1] != 92)
				count2++;
			if (quote2 == 0)
				quote2 = 1;
			else
				quote2 = 0;
		}
			
		i++;
	}

	// printf("count1 = %d     ,  count2= %d \n", count1, count2);
	
	if((count1 % 2) != 0 || (count2 % 2) != 0)
		return (0);
	return (1);
}

int shell_echo(t_command *command, t_minishell *minishell)
{

	if(validate_quotes(command->str) == 0)
	{
		ft_putstr_fd("Shell: It's not required to handle \' or \" for multiline commands \n", 1);
		return(1);
	}
	
	if(ft_strcmp(command->args[0], "-n") == 0)
	{
		echo_display(command->str, 1, minishell);
	}
	else
	{
		echo_display(command->str, 0, minishell);
		ft_putstr_fd("\n", 1);
	}
	return (1);
}
