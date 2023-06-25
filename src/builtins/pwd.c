/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:02:57 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/25 20:20:42 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	pwd(t_minishell *mini, int fd)
{
	if (!mini->env)
		return (ft_putstr_fd("pwd: couldn't find pwd\n", STDERR));
	return (ft_putstr_fd(mini->pwd, fd), ft_putchar_fd('\n', fd), 0);
}
