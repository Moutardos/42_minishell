/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:53:32 by coltcivers        #+#    #+#             */
/*   Updated: 2023/05/05 13:32:07 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		quote_check(char *line, int index)
{
	if (!line)
		return (1);
	if (quotes(line, index))
	{
		ft_putendl_fd("minishell: syntax error, quotes left open", STDERR);
		return (1);
	}
	return (0);
}

int is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '"' || c == '\'')
		return (1);
	return (0);
}

int		quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i < index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

int next_sep_pos(char *str, int pos)
{
	while (str[pos])
	{
		if (!quotes(str, INT_MAX) && is_sep(str[pos]))
			return (pos);
		pos++;
	}
	return (pos);
}
