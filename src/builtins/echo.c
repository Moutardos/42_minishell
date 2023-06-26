/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:54:22 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/26 14:22:32 by lcozdenm         ###   ########.fr       */
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
			if (ft_putchar_fd(' ', cmd->out) < 1)
				return (-1);
		if (ft_putstr_fd(av[i], cmd->out) < ft_strlen(av[i]))
			return (-1);
		i++;
	}
	if (!option)
		if (ft_putchar_fd('\n', cmd->out) < 1)
			return (-1);
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
