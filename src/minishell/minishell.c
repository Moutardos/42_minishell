/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:37:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/05/29 10:48:22 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

/// @brief Minishell struct and fields init
/// @return Newly allocated shell entity
t_minishell *init_minishell()
{
	t_minishell *mini;

	mini = ft_calloc(1, sizeof(t_minishell));
	if (!mini)
		return (NULL);
	//Ajouter ici par la suite les fieds a allouer / initialiser
	return (mini);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*curr;
	curr = cmds;
	while (curr != NULL)
	{
		//ft_free_split(curr->av);
		safe_free(curr->path);
		safe_free(curr->delim_f);
		safe_free(curr->delim);
		if (curr->next == NULL)
		{
			safe_free(curr);
			curr = NULL;
		}
		else
		{
			curr = curr->next;
			safe_free(curr->prev);
		}
	}
}

void	free_mini(t_minishell *mini)
{
	free_cmds(mini->cmds);
	ft_free_split(mini->paths);
	if (mini->env != NULL)
		//ft_lstclear( (void *) (mini->env), free);
		;
	free(mini);
}

int main(int ac, char **av)
{
	t_minishell	*mini;

	mini = init_minishell();
	//while (mini->exit == 0)
	//{
		parse_current_cmd(mini);
	//}
}