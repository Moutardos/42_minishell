/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:27:17 by hgirard           #+#    #+#             */
/*   Updated: 2023/06/27 22:31:02 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	is_valid(char *str);

int	export_m(t_minishell *mini, t_cmd *cmd)
{
	int		i;
	char	**key_val;

	i = 0;
	while (i < cmd->ac)
	{
		if (ft_strchr(cmd->av[i], '=') != NULL)
		{
			key_val = ft_split(cmd->av[i], '=');
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
		i++;
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
