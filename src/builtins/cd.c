/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:27:33 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/10 20:33:37 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
int	cd(t_minishell *mini)
{
	int		err;
	t_cmd	*cmd;

	cmd = mini->cmds;
	if (cmd->ac != 2)
		return (ft_putstr_fd("minishell: cd needs a path\n", STDERR), 0);
	err = chdir(cmd->av[1]);
	if (err)
		return (perror("minishell:"), 0);
	if (getcwd(mini->pwd, BUFFER_SIZE) == NULL)
		return (perror("minishell:"), mini->exit = -1, 0);
	if (!add_dico(mini->env, "PWD", mini->pwd))
		return (mini->exit = -1, 0);
	return (0);
}