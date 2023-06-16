/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:47:49 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/16 16:55:19 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int unset(t_minishell *mini, t_cmd *cmd)
{
	int		i;
	char	*value;
	
	i = 1;
	while (i < cmd->ac)
	{
		value = get_dico(mini->env, cmd->av[i]);
		if (!value)
			return (-1);
		if (ft_strcmp(value, ""))
		{
			if (!add_dico(mini->env, cmd->av[i], ""))
				return (-1);
		}
		safe_free(value);
		i++;
	}
	return (0);
}