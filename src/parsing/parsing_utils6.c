/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:20:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/21 15:05:05 by lcozdenm         ###   ########.fr       */
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

void	remove_quotes(t_cmd *cmds)
{
	int	i;

	while (cmds != NULL)
	{
		i = 0;
		while (cmds->av[i] != NULL)
		{
			if (cmds->av[i][0] == '\'' \
			|| cmds->av[i][0] == '"')
				cmds->av[i] = realloc_quote(cmds->av[i]);
			i++;
		}
		cmds->fname = cmds->av[0];
		cmds = cmds->next;
	}
}

//remove all ',",/ from pos 0 to next delim pos 
char	*expand_bltn(char *str)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '\\')
		{
			i++;
			continue ;
		}
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
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
	while (str[i] != '\0' && i < pos)
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '\\')
			offset++;
		i++;
	}
	return (pos - offset);
}
