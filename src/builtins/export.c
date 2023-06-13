/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:27:17 by hgirard           #+#    #+#             */
/*   Updated: 2023/06/13 20:39:24 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	export(t_minishell *mini, t_cmd *cmd)
{
	int		i;
	char	**key_val;

	i = 1;
	while (i < cmd->ac)
	{
		key_val = ft_split(cmd->av[i], '=');
		add_dico(mini->env, key_val[0], key_val[1]);
		i++;
	}
	return (0);
}
