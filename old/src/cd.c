/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ler-rech <ler-rech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 10:12:11 by ler-rech          #+#    #+#             */
/*   Updated: 2021/02/04 16:38:26 by ler-rech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int shell_cd(t_command *command)
{
  if (command->args[0] == NULL) {
    ft_putstr_fd("Shell: expected argument to \"cd\"\n", 1);
  } else {
    if (chdir(command->args[0]) != 0) {
      ft_putstr_fd("Shell: cd: ", 1);
      ft_putstr_fd(command->args[0], 1);
      ft_putstr_fd(" No such file or directory\n", 1);
      // perror("lsh"); // strerror(errno) maybe
    }
  }
  return 1;
}
