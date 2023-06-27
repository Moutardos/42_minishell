/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:56:29 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/27 14:28:38 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	exit_m(t_minishell *mini, t_cmd *cmd)
{
	extern int	g_exit_code;

	if (!cmd || (cmd && cmd->ac == 1))
	{
		mini->exit = 1;
		return (0);
	}
	if (cmd)
	{
		if (!ft_isnumeric(cmd->av[1]))
		{
			mini->exit = 1;
			ft_putendl_fd("minishell: exit: argument is not numeric", STDERR);
			return (0);
		}
		if (cmd->ac > 2)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR);
			return (0);
		}
		mini->exit = 1;
		g_exit_code = ft_atoi(cmd->av[1]);
	}
	return (0);
}
