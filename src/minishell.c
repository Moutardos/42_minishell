/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:37:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/04/28 15:13:58 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/// @brief Minishell struct and fields init
/// @return Newly allocated shell entity
t_minishell *init_minishell()
{
	t_minishell *mini;

	mini = malloc(sizeof(t_minishell));
	if (!mini)
		return (NULL);
	//Ajouter ici par la suite les fieds a allouer / initialiser
	return (mini);
}


int main(int ac, char **av)
{
	t_minishell	*mini;

	mini = init_minishell();
	while (mini->exit == 0)
	{
		parse_current_cmd(mini);
	}
}