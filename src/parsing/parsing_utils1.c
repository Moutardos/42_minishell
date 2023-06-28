/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:28:01 by hgirard           #+#    #+#             */
/*   Updated: 2023/06/28 14:32:14 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*str_fullcpy(char *src)
{
	char	*dst;
	int		i;

	i = 0 ;
	dst = ft_calloc((ft_strlen(src) + 1), sizeof(char));
	if (!dst)
		return (NULL);
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i <= index)
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

int	next_sep_pos(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes(str, pos) && str[pos] == '|')
			return (pos + 1);
		pos++;
	}
	return (pos);
}

void	get_args_auxiliary2(t_cmd *curr_cmd, char *cmd2,
t_delims_args *a)
{
	curr_cmd->av[curr_cmd->ac] = ft_calloc(a->j - a->i + 1, \
	sizeof(char));
	if (!curr_cmd->av[curr_cmd->ac])
		return ;
	while (a->i < a->j)
	{
		if ((cmd2[a->i] == '\'' || cmd2[a->i] == '"') \
		&& (!quotes2(cmd2, a->i) || (quotes2(cmd2, a->i) \
		&& !quotes2(cmd2, a->i + 1))))
		{
			a->i++;
			continue ;
		}
		curr_cmd->av[curr_cmd->ac][a->l] = cmd2[a->i];
		a->i++;
		a->l++;
	}
	curr_cmd->av[curr_cmd->ac][a->l] = '\0';
	curr_cmd->ac++;
}

int	is_sep(char c)
{
	if (c == '"' || c == '\'' || c == ' ' || c == '|' || c == '\0')
		return (1);
	return (0);
}
