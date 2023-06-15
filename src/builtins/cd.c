/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:27:33 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/15 18:54:07 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_minishell *mini)
{
	int		err;
	t_cmd	*cmd;

	cmd = mini->cmds;
	if (cmd->ac > 2)
		return (ft_putstr_fd("minishell: path not found\n", STDERR), 0);
	else if (cmd->ac == 2)
		err = chdir(cmd->av[1]);
	else
		err = chdir("/");
	if (err)
		return (perror("minishell"), 0);
	if (getcwd(mini->pwd, BUFFER_SIZE) == NULL)
		return (perror("minishell:"), mini->exit = -1, 0);
	if (!add_dico(mini->env, "PWD", mini->pwd))
		return (mini->exit = -1, 0);
	return (0);
}
