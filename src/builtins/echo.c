/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:54:22 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/25 19:45:33 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	get_options(char ***av);

int	echo(t_cmd *cmd)
{
	int		option;
	int		i;
	char	**av;

	av = cmd->av + 1;
	i = 0;
	if (!av)
		return (1);
	option = get_options(&av);
	while (av[i])
	{
		if (i != 0)
			ft_putchar_fd(' ', cmd->out);
		ft_putstr_fd(av[i], cmd->out);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', cmd->out);
	return (0);
}

static int	get_options(char ***av)
{
	char	*str;
	int		re;
	int		i;

	re = 0;
	while (**av)
	{
		str = **av;
		i = 1;
		if (str[0] != '-')
			return (re);
		while (str[i])
		{
			if (str[i] != 'n')
				return (re);
			re = 1;
			i++;
		}
		if (i == 1)
			return (re);
		*av += 1;
	}
	return (re);
}
