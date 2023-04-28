/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:30:27 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/26 14:20:09 by lcozdenm         ###   ########.fr       */
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
		"bonjour",
		NULL,
	};

	t_arg *test;
	test = malloc(sizeof(t_arg));
	if (!test)
		return (0);
	test->ac = 2;
	test->av = av_test;
	execute(test);
	return (0);
}