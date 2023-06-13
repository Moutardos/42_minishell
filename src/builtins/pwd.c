/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:02:57 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/13 20:48:17 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

int	pwd(t_minishell *mini, int fd)
{
	printf("pwd custom\n");
	return (ft_putstr_fd(mini->pwd, fd), ft_putchar_fd('\n', fd), 0);
}