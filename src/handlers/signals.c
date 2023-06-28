/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:56:07 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/28 17:25:55 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "handlers.h"
#include "builtins.h"

void	handler(int sig)
{
	extern int	g_sig_get;

	if (sig == SIGINT)
	{
		g_sig_get = 1;
		replace_line();
	}
}

int	signal_caught(t_minishell *mini)
{
	extern int	g_sig_get;

	mini->exit_code = 130;
	g_sig_get = 0;
	if (!add_dico(mini->env, "?", "130"))
		return (exit_m(mini, NULL), -1);
	return (0);
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
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
