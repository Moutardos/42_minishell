/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:48:56 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/15 17:39:51 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	closef(int fd, int new)
{
	if (fd != STDIN && fd != STDOUT && fd > 0)
		close(fd);
	return (new);
}

int	is_last_heredoc(t_cmd *cmd, int i)
{
	if (cmd->delim[i] != IN_NL)
		return (0);
	i++;
	while (cmd->delim_f[i] && cmd->delim[i] != IN_NL)
		i++;
	if (!cmd->delim_f[i])
		return (1);
	return (0);
}