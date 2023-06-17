/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:54:22 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/17 15:28:04 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	echo(t_cmd *cmd)
{
	int		nl;
	int		i;
	char	**av;

	av = cmd->av + 1;
	i = 0;
	nl = 1;
	if (!av)
		return (1);
	if (av[0] && !ft_strcmp(av[0], "-n"))
	{
		av++;
		nl = 0;
	}
	while (av[i])
	{
		if (i != 0)
			ft_putchar_fd(' ', cmd->out);
		ft_putstr_fd(av[i], cmd->out);
		i++;
	}
	if (nl)
		ft_putchar_fd('\n', cmd->out);
	return (0);
}
