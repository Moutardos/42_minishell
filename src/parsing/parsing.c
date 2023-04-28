/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:50:25 by coltcivers        #+#    #+#             */
/*   Updated: 2023/04/28 15:50:40 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "handlers.h"

/// @brief Get the latest user input and parse it into args, loop called
void parse_current_cmd(t_minishell *mini)
{
	char *line;
	t_arg *args;

	signal(SIGINT, &sig_int); //TODO
	signal(SIGQUIT, &sig_quit); //TODO 

	line = readline("minishell : \n");
	if (quote_check(line))
		return (free(line)); // TODO: check behaviors for empty inputs
	/*
	Structure du parsing :

	-Readline du current input 
	-Verifier nombres / viabilite des quotes pour s'assurer qu'elles soient fermees
	en parcourant la string
	-
	*/
	free(line);
}


static int		quote_check(char *line)
{
	if (!line)
		return (1);
	if (quotes(line))
	{
		ft_putendl_fd("minishell: syntax error, quotes left open", STDERR);
		return (1);
	}
	return (0);
}

static int		quotes(char *line)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i < INT_MAX)
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
