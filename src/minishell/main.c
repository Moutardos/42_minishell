/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:30:27 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/12 17:07:44 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	const char * av_test[] = {
		"megatest",
		"arg1",
		NULL
	};
	const char * av_test2[] = {
		"rev",
		NULL
	};

	t_cmd *arg1;
	t_cmd *arg2;

	t_minishell mini;
	arg2 = malloc(sizeof(t_cmd));
	if (!arg2)
		return (0);
	arg2->ac = 2;
	arg2->av = av_test2;
	arg2->in = 0;
	arg2->out = 1;
	arg2->delim = NULL;
	arg2->delim_f = NULL;
	arg2->next = NULL;
	arg2->path = NULL;
	arg1 = malloc(sizeof(t_cmd));
	if (!arg1)
		return (0);
	arg1->ac = 2;
	arg1->av = av_test;
	arg1->delim = malloc(sizeof(t_delim) * 1);
	arg1->delim[0] = OUT;
	arg1->delim_f = malloc(sizeof(char *) * 2);
	arg1->delim_f[0] = NULL;
	arg1->delim_f[1] = NULL;
	arg2->in = 0;
	arg2->out = 1;
	arg1->path = "bin/megatest";
	arg1->next = arg2;
	arg1->prev = NULL;
	arg2->prev = arg1;
	arg2->next = NULL;
	mini.cmds = arg1;
	mini.env = NULL;
	// if (getcwd(mini.pwd, BUFFER_SIZE) == NULL)
	// {
	// 	printf("couldn't get current working folder\n");
	// 	return (perror("minishell"),0);
	// }
	mini.paths = ft_split(getenv("PATH"), ':');
	execute(&mini);
	free(arg1);
	free(arg2);
	return (0);
}
