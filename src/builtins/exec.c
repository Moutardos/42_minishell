/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:42:56 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/28 15:22:35 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	execute(t_arg	*args)
{
	const char	*fname;
	pid_t	pid;

	if (args->ac < 1)
		return (1); //TODO, renvoyé l'erreur avec un type t_error?
	fname = args->av[0];
	pid = fork();
	if (pid == F_ERROR) // Error
		return (1);
	else if (pid == F_SON) // le fils execute le prog
		execve(fname, args->av, NULL); //dernier arg est l'env
	else // le pere attend
	{
		wait(F_SON);
	}
	return (0);
}