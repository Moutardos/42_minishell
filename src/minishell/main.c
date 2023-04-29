/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:30:27 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/29 18:42:32 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	const char * av_test[] = {
		"echo",
		"arg1",
		NULL,
	};
	const char * av_test2[] = {
		"read",
		"arg2",
		NULL,
	};

	t_arg *arg1;
	t_arg *arg2;
	arg2 = malloc(sizeof(t_arg));
	if (!arg2)
		return (0);
	arg2->ac = 2;
	arg2->av = av_test2;
	arg2->next = NULL;
	arg2->is_piped = 0;
	arg2->prev = arg1;
	arg2->pipe[0] = STDIN;
	arg2->pipe[1] = STDOUT;
	arg1 = malloc(sizeof(t_arg));
	if (!arg1)
		return (0);
	arg1->ac = 2;
	arg1->av = av_test;
	arg1->next = arg2;
	arg1->is_piped = 0;
	arg1->prev = NULL;
	arg1->pipe[0] = STDIN;
	arg1->pipe[1] = STDOUT;

	execute(arg1);
	return (0);
}