/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:42:56 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/29 18:00:17 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	repipe(t_arg *out, t_arg *in, int *pip);
 
int	execute(t_arg	*args)
{
	const char	*fname;
	pid_t	pid;
	int	pip[2];

	if (args->ac < 1)
		return (1); //TODO, renvoyé l'erreur avec un type t_error?
	while (args != NULL)
	{
		pipe(pip);
		fname = args->av[0];
		pid = fork();
		if (pid == F_ERROR)
			return (1);
		else if (pid == F_SON)
		{
			repipe(args, args->next, pip);
			execve(fname, args->av, NULL);
		}
		else
		{
			args = args->next;
		}
	}
	while(wait(NULL) > 0);
	return (0);
}

static int	repipe(t_arg *out, t_arg *in, int *pip)
{
	if (out == NULL || in == NULL || pip == NULL)
		return (1);
    dup2(pip[0], out->pipe[1]);
    dup2(pip[1], in->pipe[0]);
	close(pip[0]);
    close(pip[1]);
	return (0);
}