/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:27:17 by hgirard           #+#    #+#             */
/*   Updated: 2023/06/25 19:11:58 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int    export_m(t_minishell *mini, t_cmd *cmd)
{
    int        i;
    char    **key_val;

    i = 1;
    while (i < cmd->ac)
    {
        if (ft_strchr(cmd->av[i], '=') != NULL)
        {
            key_val = ft_split(cmd->av[i], '=');
            if (!key_val)
              return (exit_m(mini, NULL), -1);
            if (!key_val[0])
              ft_free_split(key_val);
            else if (!key_val[1])
            {
                if (!add_dico(mini->env, !key_val[0], ""))
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
