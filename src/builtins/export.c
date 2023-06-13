/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:27:17 by hgirard           #+#    #+#             */
/*   Updated: 2023/06/13 21:25:37 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int export_m(t_minishell *mini, t_cmd *cmd)
{
	printf("export builtlin \n");
	int 	i;
	char	**key_val;
	i = 1;
	while (i < cmd->ac)
	{
		key_val = ft_split(cmd->av[i], '=');
		printf("key : %s\n", key_val[0]);
		printf("value : %s\n", key_val[1]);
		add_dico(mini->env, key_val[0],key_val[1]);
		i++;
	}
	return (0);
}