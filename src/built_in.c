/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/01/26 16:32:40 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int shell_cd(char **args)
{
  if (args[1] == NULL) {
    ft_putstr_fd("Shell: expected argument to \"cd\"\n", 1);
  } else {
    if (chdir(args[1]) != 0) {
      ft_putstr_fd("Shell: cd: ", 1);
      ft_putstr_fd(args[1], 1);
      ft_putstr_fd(" No such file or directory\n", 1);
      // perror("lsh"); // strerror(errno) maybe
    }
  }
  return 1;
}



int shell_exit(char **args)
{
  if(args[1] != NULL)
  {
    ft_putstr_fd("Shell: Exist must be with no options \n", 1); 
    return (1);
  }
  return (0);
}