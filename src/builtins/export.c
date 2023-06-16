/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:27:17 by hgirard           #+#    #+#             */
/*   Updated: 2023/06/16 16:43:38 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	export_m(t_minishell *mini, t_cmd *cmd)
{
	int		i;
	char	**key_val;

	i = 1;
	while (i < cmd->ac)
	{
		if (ft_strchr(cmd->av[i], '=') != NULL)
		{
			key_val = ft_split(cmd->av[i], '=');
			if (!key_val)
				return (-1);
			add_dico(mini->env, key_val[0], key_val[1]);
			ft_free_split(key_val);
		}
		i++;
	}
	return (0);
}
