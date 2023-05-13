/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:30:27 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/13 14:34:12 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	//megatest c'est un prog random qui affiche le premier argument
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

	// On imagine "rev < why"
	arg2 = malloc(sizeof(t_cmd));
	if (!arg2)
		return (0);
	arg2->ac = 2;
	arg2->av = av_test2;
	arg2->in = 0;
	arg2->out = 1;
	arg2->delim = malloc(sizeof(t_delim) * 2);
	arg2->delim[0] = IN;
	arg2->delim_f = malloc(sizeof(char *) * 2);
	arg2->delim_f[0] = "why";
	arg2->delim_f[1] = NULL;
	arg2->path = NULL;

	// On imagine "./megatest > result >> why"
	arg1 = malloc(sizeof(t_cmd));
	if (!arg1)
		return (0);
	arg1->ac = 2;
	arg1->av = av_test;
	arg1->delim = malloc(sizeof(t_delim) * 2);
	arg1->delim[0] = OUT;
	arg1->delim[1] = OUT_APPEND;
	arg1->delim_f = malloc(sizeof(char *) * 3);
	arg1->delim_f[0] = "resultat";
	arg1->delim_f[1] = "why";
	arg1->delim_f[2] = NULL;
	arg1->in = 0;
	arg1->out = 1;
	arg1->path = "./megatest";
	
	arg2->next = NULL;
	arg1->next = arg2;
	arg1->prev = NULL;
	
	mini.cmds = arg1;
	mini.env = NULL;
	// if (getcwd(mini.pwd, BUFFER_SIZE) == NULL)
	// {
	// 	printf("couldn't get current working folder\n");
	// 	return (perror("minishell"),0);
	// }

	//paths par defaut 
	mini.paths = ft_split(getenv("PATH"), ':');
	
	// commande : "./megatest > result >> why | rev < why"
	execute(&mini);
	free(arg1);
	free(arg2);
	return (0);
}
