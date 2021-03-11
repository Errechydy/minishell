/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/03/11 17:34:09 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int shell_cd(t_command *command, char **env)
{
  
  
  if(command->full_args[1] == NULL)
    chdir(get_env_value("HOME", env));
  else
    if(chdir(command->full_args[1]) != 0) {
      ft_putstr_fd("Minishell: cd: ", 2);
      ft_putstr_fd(command->full_args[1], 2);
      ft_putstr_fd(" No such file or directory\n", 2);
      g_last_exec = 1;
    }
    else
      g_last_exec = 0;
  return 1;
}
