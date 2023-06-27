/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:31:06 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/28 00:04:50 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	assign_delims_offset(char *cmd, int *data, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if ((cmd[j] == '>' || cmd[j] == '<') && i != 0)
		{
			j++;
			continue ;
		}
		j = get_next_delim(cmd, j);
		data[i] = curr_delim_offset(cmd, j);
		i++;
	}
	data[i] = ft_strlen(cmd);
}

void	get_delims_auxiliary3(t_delims_args *args, \
char *cmd, char *holder)
{
	while (args->i < args->j)
	{
		holder[args->l] = cmd[args->i];
		args->i++;
		args->l++;
	}
	holder[args->l] = '\0';
	args->delim_b++;
}

void	set_builtins(t_cmd *cmd)
{
	if (cmd->fname)
	{
		if (!ft_strcmp(cmd->fname, "echo"))
			cmd->builtin = ECHO;
		else if (!ft_strcmp(cmd->fname, "pwd"))
			cmd->builtin = PWD;
		else if (!ft_strcmp(cmd->fname, "cd"))
			cmd->builtin = CD;
		else if (!ft_strcmp(cmd->fname, "env"))
			cmd->builtin = ENV;
		else if (!ft_strcmp(cmd->fname, "export"))
			cmd->builtin = EXPORT;
		else if (!ft_strcmp(cmd->fname, "unset"))
			cmd->builtin = UNSET;
		else if (!ft_strcmp(cmd->fname, "exit"))
			cmd->builtin = EXIT;
		else
			cmd->builtin = B_NONE;
	}
	else
		cmd->builtin = B_NONE;
}

int	is_delim2(char *cmd, int i)
{
	if (!quotes(cmd, i) && (cmd[i] == '>' || cmd[i] == '<'))
		return (1);
	return (0);
}

int	quotes2(char *line, int index)
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
