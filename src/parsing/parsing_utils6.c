/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:20:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/28 00:07:49 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*realloc_quote(char *str)
{
	char		*new;
	size_t		i;

	new = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	if (!new)
		return (NULL);
	i = 0;
	while (i < ft_strlen(str) - 2)
	{
		new[i] = str[i + 1];
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

static int	quotes_test(char *line, int index)
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

char	*expand_bltn(char *str, int i)
{
	char	*new;
	int		j;
	int		value;

	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new)
		return (NULL);
	j = 0;
	while (str[i] != '\0')
	{
		value = 0;
		if (quotes_test(str, i))
			value = 1;
		if (!quotes_test(str, i + value) && (str[i] == '"' \
		|| str[i] == '\'' || str[i] == '\\'))
		{
			i++;
			continue ;
		}
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (free(str), new);
}

int	next_arg_pos3(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes(str, pos))
		{
			while (!quotes(str, pos) && str[pos] != ' ' && str[pos] != '\0')
				pos++;
			return (pos);
		}
		if (quotes(str, pos))
		{
			while (quotes(str, pos))
				pos++;
			return (pos + 1);
		}
		pos++;
	}
	return (pos);
}

int	curr_delim_offset(char *str, int pos)
{
	int	i;
	int	offset;

	i = 0;
	offset = 0;
	while (str[i] != '\0' && i <= pos)
	{
		if ((!quotes_test(str, i) || (quotes_test(str, i) && \
		!quotes_test(str, i + 1))) \
		&& (str[i] == '"' || str[i] == '\'' || str[i] == '\\'))
			offset++;
		i++;
	}
	return (pos - offset);
}
