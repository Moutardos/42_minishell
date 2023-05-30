/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgirard <hgirard@student.42.f>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:48:51 by hgirard           #+#    #+#             */
/*   Updated: 2023/05/27 23:18:03 by hgirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_delim	get_curr_delim(char *str, int pos)
{
	if (str[pos] == '>')
	{
		if (str[pos + 1] == '>')
			return (OUT_APPEND);
		return (OUT);
	}
	else if (str[pos] == '<')
	{
		if (str[pos + 1] == '<')
			return (IN_NL);
		return (IN);
	}
	return (NONE);
}

int	bltn_args_amount(char *cmd)
{
	int	i;
	int	count;

	i = get_post_bltn(cmd);
	count = 0;
	while (cmd[i] != '\0' && !is_delim(cmd, i))
	{
		if (cmd[i] != ' ')
		{
			i = next_arg_pos(cmd, i);
			count++;
			continue ;
		}
		i++;
	}
	return (count);
}

void	*clear_cmd(t_cmd	*cmd)
{
	while (cmd->next != NULL)
		cmd_del_last(cmd);
	cmd_del_cmd(cmd);
	return (NULL);
}
