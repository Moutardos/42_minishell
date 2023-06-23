/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:31:06 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/23 17:54:53 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	assign_delims_offset(char *cmd, char *cmd2, int *data, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (is_delim(cmd, j) && i != 0)
		{
			j++;
			continue ;
		}
		j = get_next_delim(cmd, j);
		data[i] = curr_delim_offset(cmd, j);
		i++;
	}
	data[i] = ft_strlen(cmd2);
}

//echo salut"toi >>> || |" "|" > test."txt" append" append2" ">"
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
