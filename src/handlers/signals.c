/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:56:07 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/19 16:11:37 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "handlers.h"
void	handler(int sig, siginfo_t *info, void *c)
{
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	if (sig == SIGQUIT)
		return ;
	if (sig == SIGINT)
		replace_line();
}

void	setup_signals(void handler(int, siginfo_t, void*))
{
	struct sigaction	sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	replace_line(void)
{
	ft_printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0); enlever le comm
	rl_redisplay();
}
