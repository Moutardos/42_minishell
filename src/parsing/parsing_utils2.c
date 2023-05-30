/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgirard <hgirard@student.42.f>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:29:02 by hgirard           #+#    #+#             */
/*   Updated: 2023/05/27 22:48:07 by hgirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delim(char *cmd, int i)
{
	if (!quotes(cmd, i) && (cmd[i] == '>' || cmd[i] == '<' || cmd[i] == '|'))
		return (1);
	return (0);
}

int	get_post_bltn(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	next_arg_pos(char *str, int pos)
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

int	get_delims_amount(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if ((str[i] == '>' && str[i + 1] == '>') \
			|| (str[i] == '<' && str[i + 1] == '<'))
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int	get_next_delim(char *str, int start)
{
	int	i;

	i = start;
	while (str[i] != '\0' && str[i] != '>' && str[i] != '<')
		i++;
	return (i);
}
