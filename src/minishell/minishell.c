/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:37:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/27 17:29:38 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "handlers.h"

int	g_exit_code = 0;

/// @brief Minishell struct and fields init
/// @return Newly allocated shell entity
t_minishell	*init_minishell(char **envp)
{
	t_minishell	*mini;

	mini = ft_calloc(1, sizeof(t_minishell));
	if (!mini)
		return (NULL);
	mini->env = array_dico(envp);
	if (getcwd(mini->pwd, BUFFER_SIZE) == NULL)
		mini->pwd[0] = '\0';
	if (!add_dico(mini->env, "?", "0"))
		return (free_dico(&mini->env), safe_free(mini), NULL);
	mini->paths = NULL;
	mini->hd_path = ft_strjoin(mini->pwd, "/.hd");
	if (!mini->hd_path)
	{
		ft_free_split(mini->paths);
		return (free_dico(&mini->env), safe_free(mini), NULL);
	}
	return (mini);
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*curr;
	t_cmd	*prev;

	curr = *cmds;
	while (curr != NULL)
	{
		ft_free_split(curr->av);
		safe_free(curr->path);
		ft_free_split(curr->delim_f);
		safe_free(curr->delim);
		safe_free(curr->offset_delims);
		if (curr->next == NULL)
		{
			safe_free(curr);
			curr = NULL;
		}
		else
		{
			prev = curr;
			curr = curr->next;
			safe_free(prev);
		}
	}
	*cmds = NULL;
}

static void	free_mini(t_minishell **mini)
{
	t_minishell	*curr;

	curr = *mini;
	if (curr->cmds)
		free_cmds(&curr->cmds);
	if (curr->paths)
		ft_free_split(curr->paths);
	if (curr->env)
		free_dico(&curr->env);
	safe_free(curr->hd_path);
	safe_free(curr);
	*mini = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*mini;

	(void)ac;
	(void)av;
	setup_signals(handler);
	mini = init_minishell(envp);
	if (!mini)
		return (-1);
	while (!mini->exit)
	{
		if (parse_current_cmd(mini) < 0)
			continue ;
		if (mini->cmds)
		{
			execute(mini);
			free_cmds(&mini->cmds);
		}
	}
	free_mini(&mini);
	return (g_exit_code);
}
