/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:31:06 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/27 17:57:46 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

//echo salut toi " ||||| || | || " > test".txt" append2">" "|||"
void	assign_delims_offset(char *cmd, char *cmd2, int *data, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	//printf("assign cmd : %s\n", cmd);
	//printf("assign cmd2 : %s\n", cmd2);
	while (i < size)
	{
		//if (is_delim(cmd2, j) && i != 0)
		if ((cmd[j] == '>' || cmd[j] == '<') && i != 0)
		{
			j++;
			continue ;
		}
		j = get_next_delim(cmd, j);
		//printf("j : %d\n", j);
		//printf("curr_delim_offset(cmd, j) : %d\n", curr_delim_offset(cmd, j));
		data[i] = curr_delim_offset(cmd, j);
		//j = get_next_delim(cmd2, j);
		//data[i] = j;
		//printf("data[i] : %d\n", data[i]);
		//printf("cmd[data[i]] : %c\n", cmd[data[i]]);
		//printf("cmd[data[i] : %c\n", cmd[data[i] + 1]);
		//printf("get_next_delim(cmd2, 0) : %d\n", get_next_delim(cmd2, 0));
		//delim_offset = curr_delim_offset(cmd2, get_next_delim(cmd2, 0));
		i++;
	}
	data[i] = ft_strlen(cmd);
	//printf("data[i] : %d\n", data[i]);
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
	//printf("holder : %s\n", holder);
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
