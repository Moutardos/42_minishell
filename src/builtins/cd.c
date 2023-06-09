/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:27:33 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/27 21:59:16 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	cd(t_minishell *mini, t_cmd *cmd)
{
	int		err;
	char	*home;

	if (cmd->ac > 2)
		return (ft_putstr_fd("minishell: too much arguments\n", STDERR), 0);
	else if (cmd->ac == 2)
		err = chdir(cmd->av[1]);
	else
	{
		home = get_dico(mini->env, "HOME");
		if (!home)
			return (ft_putstr_fd("cd: couldn't find home\n", STDERR), 0);
		err = chdir(home);
		safe_free(home);
	}
	if (err < 0)
		return (perror("minishell"), 0);
	if (getcwd(mini->pwd, BUFFER_SIZE) == NULL)
		return (mini->pwd[0] = '\0', 0);
	if (!add_dico(mini->env, "PWD", mini->pwd))
		return (exit_m(mini, NULL), 0);
	return (0);
}
