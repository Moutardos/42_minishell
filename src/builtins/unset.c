/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:47:49 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/25 18:30:14 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	unset(t_minishell *mini, t_cmd *cmd)
{
	int		i;
	char	*key;
	t_dico	*dico;

	i = 1;
	while (i < cmd->ac)
	{
		dico = mini->env;
		while (dico)
		{
			key = dico->key;
			if (!ft_strcmp(key, cmd->av[i]))
			{
				delete_dico(mini->env, cmd->av[i]);
			}
			dico = dico->next;
		}
		i++;
	}
	return (0);
}
