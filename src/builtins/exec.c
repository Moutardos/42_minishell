/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:42:56 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/29 19:24:51 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	repipe(t_arg *out, t_arg *in, int *pip);
 
int	execute(t_arg	*args)
{
	const char	*fname;
	int	pip[2];

	if (args->ac < 1)
		return (1); //TODO, renvoyé l'erreur avec un type t_error?
	while (args != NULL)
	{
		pipe(pip);
		fname = args->av[0];
		child(args);
		args = args->next;
		}
	}
	while(wait(NULL) > 0);
	return (0);
}

static void	child(t_args *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == F_CHILD)
	{
		if (cmd->prev == NULL)
		{
			dupinout(cmd->pipe[0], cmd->pipe[1]);//check
		}
	}
}
static void	dupinout(int in, int out)
{
	dup2(in, STDIN);
	dup2(out, STDOUT);
}