/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:50:25 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/07 17:46:28 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static char	*parse_cmd_auxiliary(char *str, int start, int end, int j)
{
	char	*temp;

	temp = ft_calloc(end - start + 1, sizeof(char));
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
	if (!validate_builtin(builtin))
		printf("Unsuported builtin provided, still going on\n");
	cmd = new_cmd();
	copy = str_fullcpy(temp);
	copy2 = str_fullcpy(temp);
	get_args(cmd, copy, builtin);
	get_delims(cmd, ft_calloc(sizeof(t_delims_args), 1), copy2);
	cmd->in = STDIN;
	cmd->out = STDOUT;
	free(temp);
	free(copy);
	free(copy2);
	return (cmd);
}

static t_cmd	*parser(char *str)
{
	int		i;
	int		next_delim;
	t_cmd	*curr_cmd;
	t_cmd	*new_cmd;

	i = 0;
	curr_cmd = NULL;
	printf("full cmd : %s\n", str);
	while (str[i] != '\0')
	{
		next_delim = next_sep_pos(str, i);
		new_cmd = parse_cmd(i, next_delim, str);
		if (!new_cmd)
			return (clear_cmd(curr_cmd));
		cmd_add_back(&curr_cmd, new_cmd);
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
		while (i < new_cmd->delim_amount)
		{
			printf("delim : %d\n", new_cmd->delim[i]);
			printf("delim_f : %s\n", new_cmd->delim_f[i]);
			i++;
		}
	i = next_delim;
	}
	return (curr_cmd);
}

/// @brief Get the latest user input and parse it into args, loop called
void	parse_current_cmd(t_minishell *mini)
{
	char	*line;
	t_cmd	*cmds;

	//signal(SIGINT, &sig_int);
	//signal(SIGQUIT, &sig_quit);
	line = readline("minishell : ");
	if (quotes(line, ft_strlen(line)))
		return (free(line));
	line = replace_str2(mini->env, line);
	cmds = parser(line);
	if (cmds)
		mini->cmds = cmds;
	free(line);
}
