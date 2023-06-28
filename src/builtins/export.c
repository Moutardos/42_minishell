/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:27:17 by hgirard           #+#    #+#             */
/*   Updated: 2023/06/28 16:28:25 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	is_valid(char *str);

int	export_m(t_minishell *mini, t_cmd *cmd)
{
	char	**key_val;
	char	**av;

	av = cmd->av + 1;
	while (*av)
	{
		if (ft_strchr(*av, '=') != NULL)
		{
			key_val = ft_split(*av, '=');
			if (!key_val)
				return (exit_m(mini, NULL), -1);
			if (!key_val[0] || !is_valid(key_val[0]))
				;
			else if (!key_val[1])
			{
				if (!add_dico(mini->env, key_val[0], ""))
					return (ft_free_split(key_val), exit_m(mini, NULL), -1);
			}
			else if (!add_dico(mini->env, key_val[0], key_val[1]))
				return (ft_free_split(key_val), exit_m(mini, NULL), -1);
			ft_free_split(key_val);
		}
		av += 1;
	}
	return (0);
}

static int	is_valid(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
		{
			ft_putstr_fd("minishell: export: character not valid\n", STDERR);
			return (0);
		}
		str++;
	}
	return (1);
}
