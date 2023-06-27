/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:08:08 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/27 23:28:36 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	next_arg_pos2(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes(str, pos))
		{
			while (!quotes(str, pos) && str[pos] != ' ' && str[pos] != '\0' \
			&& !is_delim(str, pos))
				pos++;
			return (pos);
		}
		if (quotes(str, pos))
		{
			while (quotes(str, pos) && str[pos] != ' ' && str[pos] != '$')
				pos++;
			return (pos);
		}
		pos++;
	}
	return (pos);
}

int	replace_case(char *str, int pos)
{
	int	i;

	i = pos;
	while (i > 0 && quotes2(str, i))
		i--;
	if (str[i] == '\'')
		return (0);
	return (1);
}

int	next_arg_pos4(char *str, int pos)
{
	while (str[pos] != ' ' && str[pos] != '\0')
		pos++;
	return (pos);
}

int	next_arg_pos_temp(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes2(str, pos) && (str[pos] == ' ' \
		|| str[pos] == '>' || str[pos] == '<'))
			return (pos);
		pos++;
	}
	return (pos);
}

void	parse_current_cmd_utils(t_cmd *cmds)
{
	while (cmds != NULL)
	{
		cmds->fname = cmds->av[0];
		set_builtins(cmds);
		cmds = cmds->next;
	}
}
