/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:56:29 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/20 23:30:35 by lcozdenm         ###   ########.fr       */
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
			return (ft_printf("minishell: exit: argument is not numeric"), 1);
		mini->exit = 1;
		if (cmd->ac > 2)
			return (ft_printf("minishell: exit: too many arguments"), 1);
		g_exit_code = ft_atoi(cmd->av[1]);
	}
	return (0);
}
