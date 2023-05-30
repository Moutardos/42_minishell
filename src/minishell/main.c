/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:30:27 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/29 09:38:16 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/*
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	//megatest c'est un prog random qui affiche le premier argument
	const char * av_test[] = {
		"rev",
		NULL,
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
	arg2->delim = malloc(sizeof(t_delim) * 2);
	arg2->delim[0] = IN;
	arg2->delim_f = malloc(sizeof(char *) * 2);
	arg2->delim_f[0] = NULL;
	arg2->delim_f[1] = NULL;
	arg2->path = NULL;

	arg1 = malloc(sizeof(t_cmd));
	if (!arg1)
		return (0);
	arg1->ac = 2;
	arg1->av = av_test;
	arg1->delim = malloc(sizeof(t_delim) * 2);
	arg1->delim[0] = IN_NL;
	arg1->delim[1] = IN_NL;
	arg1->delim_f = malloc(sizeof(char *) * 3);
	arg1->delim_f[0] = "k";
	arg1->delim_f[1] = "non";
	arg1->delim_f[2] = NULL;
	arg1->in = 0;
	arg1->out = 1;
	arg1->path = NULL;
	
	arg2->next = NULL;
	arg2->prev = arg1;
	arg1->next = arg2;
	arg1->prev = NULL;
	
	mini.cmds = arg1;
	mini.env = NULL;
	if (getcwd(mini.pwd, BUFFER_SIZE) == NULL)
	{
		printf("couldn't get current working folder\n");
		return (perror("minishell"),0);
	}

	//paths par defaut 
	mini.paths = ft_split(getenv("PATH"), ':');
	printf("rev << k << non\n");
	// commande : "./megatest > result >> why | rev < why"
	execute(&mini);
	free_cmds(arg1);
	ft_free_split(mini.paths);
	t_dico *dico;
	dico = init_dico("coucou", "bonjour");
	add_dico(dico, "hey", "salut");
	add_dico(dico, "hey", "salut2");
	char **e = array_dico(dico);
	return (0);
}
*/