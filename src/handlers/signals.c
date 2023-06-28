/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:56:07 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/28 13:47:14 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "handlers.h"

void	handler(int sig)
{
	extern int	g_sig_get;

	if (sig == SIGINT)
	{
		g_sig_get = 1;
		replace_line();
	}
}

void	setup_signals(void handler(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	replace_line(void)
{
	ft_printf("\n");
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
