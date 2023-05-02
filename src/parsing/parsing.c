/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:50:25 by coltcivers        #+#    #+#             */
/*   Updated: 2023/05/02 15:56:08 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Get the latest user input and parse it into args, loop called
void parse_current_cmd(t_minishell *mini)
{
	char *line;
	t_cmd *cmd;

	signal(SIGINT, &sig_int); //TODO
	signal(SIGQUIT, &sig_quit); //TODO 

	line = readline("minishell : \n");
	if (quote_check(line))
		return (free(line)); // TODO: check behaviors for empty inputs
	assign_cmds(line);
	/*
	Structure du parsing :

	-Readline du current input 
	-Verifier nombres / viabilite des quotes pour s'assurer qu'elles soient fermees
	en parcourant la string
	-
	*/
	free(line);
}

void	assign_cmds(char *str)
{
	int	i;
	int j;
	char *current_cmd;
	
	i = 0;
	j = -1;
	while (str[i] != '\0')
	{
		if (!quotes(str, i) && is_sep(str[i]))
		{
			current_cmd = malloc(sizeof(char) * (i + 1));
			while (j++ < i)
				current_cmd[j] = str[j];
			current_cmd[j] = '\0';
		}
		i++;
	}
}