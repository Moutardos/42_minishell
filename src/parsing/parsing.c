/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:50:25 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/27 18:18:04 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "builtins.h"
#include <stdio.h>

static char *parse_cmd_auxiliary(char *str, int start, int end, int j)
{
	char *temp;

	temp = ft_calloc(end - start + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (start < end)
	{
		temp[j] = str[start];
		start++;
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

t_cmd *parse_cmd(int start, int end, char *str)
{
	char *temp;
	char *copy;
	char *copy2;
	char *builtin;
	t_cmd *cmd;

	if (delims_args_amount(str) < get_delims_amount(str))
	{
		ft_printf("mnishell: parsing error\n");
		return (NULL);
	}
	temp = parse_cmd_auxiliary(str, start, end, 0);
	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	copy = str_fullcpy(temp);
	copy = expand_bltn(copy);
	copy2 = str_fullcpy(temp);
	builtin = get_builtin(copy);
	get_args(cmd, copy, copy2, builtin);
	//printf("past get_args\n");
	get_delims(cmd, ft_calloc(sizeof(t_delims_args), 1), copy, copy2);
	//printf("past get_delims\n");
	cmd->in = STDIN;
	cmd->out = STDOUT;
	return (safe_free(temp), safe_free(copy), safe_free(copy2), cmd);
}

static int check_empty(char *str, int pos)
{
	//if (pos > 0 && str[pos - 1] == '|')
	//	return (1);
	if (str[pos] == '\0' && (pos > 0 && str[pos - 1] != '|'))
		return (0);
	while(str[pos] != '\0')
	{
		if (str[pos] != ' ')
			return (0);
		pos++;
	}
	return (1);
}

static t_cmd *parser(char *str)
{
	int i;
	int next_delim;
	t_cmd *curr_cmd;
	t_cmd *new_cmd;
	int temp;

	i = 0;
	temp = 0;
	curr_cmd = NULL;
	while (str[i] != '\0')
	{
		next_delim = next_sep_pos(str, i);
		//printf("str[next_delim] : %c\n", str[next_delim]);
		//printf("iteration : \n");
		//check if post | is empty
		//printf("check_empty(str, next_delim) : %d\n",  check_empty(str, next_delim));
		if (check_empty(str, next_delim))
			return (clear_cmd(curr_cmd));
		new_cmd = parse_cmd(i, next_delim, str);
		if (!new_cmd)
			return (clear_cmd(curr_cmd));
		if (new_cmd->av[0] != NULL && ft_strchr(new_cmd->av[0], '/'))
		{
			new_cmd->path = ft_strdup(new_cmd->av[0]);
			if (!new_cmd->path)
				return (clear_cmd(new_cmd), NULL);
		}
		cmd_add_back(&curr_cmd, new_cmd);
		/*
		printf("=============\n");
		printf("Builtin args : \n");
	i = 0;
	while (new_cmd->av[i] != NULL)
	{
		printf("arg : %s\n", new_cmd->av[i]);
		i++;
	}
	printf("/////////////\n");
	printf("Builtin redirections : \n");
	i = 0;
	while (i < new_cmd->delim_a)
	{
		printf("delim : %d\n", new_cmd->delim[i]);
		printf("delim_f : %s\n", new_cmd->delim_f[i]);
		i++;
	}
		*/
		i = next_delim;
	}
	return (curr_cmd);
}

/// @brief Get the latest user input and parse it into args, loop called
int parse_current_cmd(t_minishell *mini)
{
	char *line;

	line = readline("minishell : ");
	add_history(line);
	if (!line)
		return (exit_m(mini, mini->cmds), -1);
	if (quotes(line, ft_strlen(line)))
		return (free(line), -1);
	line = replace_str2(mini->env, line);
	mini->cmds = parser(line);
	if (!mini->cmds)
		return (safe_free(line), -1);
	parse_current_cmd_utils(mini->cmds);
	return (safe_free(line), 0);
}
