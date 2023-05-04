/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:30:27 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/04 18:59:47 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	arg2->out = open("oki", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	arg2->in = STDIN;
	arg2->next = NULL;
	arg1 = malloc(sizeof(t_cmd));
	if (!arg1)
		return (0);
	arg1->ac = 2;
	arg1->av = av_test;
	arg1->out = STDOUT;
	arg1->in = STDIN;
	arg1->next = arg2;
	arg1->prev = NULL;
	arg2->prev = arg1;
	execute(arg1);
	free(arg1);
	free(arg2);
	return (0);
}
