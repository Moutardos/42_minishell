/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:50:25 by coltcivers        #+#    #+#             */
/*   Updated: 2023/05/29 10:06:38 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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
		i = next_delim;
	}
	clear_cmd(curr_cmd);
}

/// @brief Get the latest user input and parse it into args, loop called
void	parse_current_cmd(t_minishell *mini)
{
	char	*line;

	//signal(SIGINT, &sig_int);
	//signal(SIGQUIT, &sig_quit);
	line = readline("minishell : ");
	if (quotes(line, ft_strlen(line)))
		return (free(line));
	parser(line);
	free(line);
}
