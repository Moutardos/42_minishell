/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:54:22 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/09 16:45:12 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_cmd *cmd)
{
	int		nl;
	char	**av;

	av = cmd->av + 1;
	nl = 1;
	if (!av)
		return (1);
	if (av[0] && !ft_strcmp(av[0], "-n"))
	{
		av++;
		nl = 0;
	}
	while (*av)
	{
		ft_putstr_fd(*av, cmd->out);
		av++;
	}
	if (nl)
		ft_putchar_fd('\n', cmd->out);
	return (0);
}