/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:47:49 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/28 15:54:36 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	unset(t_minishell *mini, t_cmd *cmd)
{
	char	**av;
	t_dico	*dico;

	av = cmd->av + 1;
	while (av)
	{
		dico = mini->env;
		while (dico)
		{
			if (!ft_strcmp(dico->key, *av))
			{
				delete_dico(&mini->env, *av);
				if (!mini->env)
				{
					mini->env = init_dico(NULL, NULL);
					if (!mini->env)
						return (exit_m(mini, NULL), -1);
				}
				return (0);
			}
			dico = dico->next;
		}
		av += 1;
	}
	return (0);
}
