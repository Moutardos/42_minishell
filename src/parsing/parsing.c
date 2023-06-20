/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:50:25 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/20 16:27:29 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "builtins.h"
#include <stdio.h>

static char	*parse_cmd_auxiliary(char *str, int start, int end, int j)
{
	char	*temp;

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

t_cmd	*parse_cmd(int start, int end, char *str)
{
	char			*temp;
	char			*copy;
	char			*copy2;
	char			*builtin;
	t_cmd			*cmd;

	temp = parse_cmd_auxiliary(str, start, end, 0);
	builtin = get_builtin(temp);
	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	copy = str_fullcpy(temp);
	copy = expand_bltn(copy);
	copy2 = str_fullcpy(temp);
	get_args(cmd, copy, copy2, builtin);
	get_delims(cmd, ft_calloc(sizeof(t_delims_args), 1), copy, copy2);
	cmd->in = STDIN;
	cmd->out = STDOUT;
	cmd->fname = cmd->av[0];
	return (safe_free(temp), safe_free(copy), safe_free(copy2), cmd);
}

static t_cmd	*parser(char *str)
{
	int		i;
	int		next_delim;
	t_cmd	*curr_cmd;
	t_cmd	*new_cmd;

	i = 0;
	curr_cmd = NULL;
	//printf("full cmd : %s\n", str);
	while (str[i] != '\0')
	{
		next_delim = next_sep_pos(str, i);
		new_cmd = parse_cmd(i, next_delim, str);
		if (!new_cmd)
			return (clear_cmd(curr_cmd));
		if (ft_strchr(new_cmd->av[0], '/'))
		{
			new_cmd->path = ft_strdup(new_cmd->av[0]);
			if (!new_cmd->path)
				return (clear_cmd(new_cmd), NULL);
		}
		cmd_add_back(&curr_cmd, new_cmd);
		i = next_delim;
	}
	return (curr_cmd);
}

/// @brief Get the latest user input and parse it into args, loop called
int	parse_current_cmd(t_minishell *mini)
{
	char	*line;

	line = readline("minishell : ");
	add_history(line);
	if (!line)
		return (perror("minishell:"), exit_m(), -1);
	if (quotes(line, ft_strlen(line)))
		return (free(line), 1);
	line = replace_str2(mini->env, line);
	mini->cmds = parser(line);
	if (!mini->cmds)
		return (safe_free(line), -1);
	remove_quotes(mini->cmds);		
	return (safe_free(line), 0);
}

