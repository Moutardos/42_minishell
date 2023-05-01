/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:30:27 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/01 13:15:30 by lcozdenm         ###   ########.fr       */
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

	t_cmd *arg1;
	t_cmd *arg2;
	arg2 = malloc(sizeof(t_cmd));
	if (!arg2)
		return (0);
	arg2->ac = 2;
	arg2->av = av_test2;
	arg2->next = NULL;
	arg1 = malloc(sizeof(t_cmd));
	if (!arg1)
		return (0);
	arg1->ac = 2;
	arg1->av = av_test;
	arg1->next = arg2;
	arg1->prev = NULL;
	arg2->prev = arg1;
	execute(arg1);
	free(arg1);
	free(arg2);
	return (0);
}
