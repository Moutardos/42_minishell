/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:37:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/28 15:46:15 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include "handlers.h"
#include "builtins.h"

int	g_sig_get = 0;
static t_dico	*create_env(t_minishell *mini, char **envp);

/// @brief Minishell struct and fields init
/// @return Newly allocated shell entity
t_minishell	*init_minishell(char **envp, char *v)
{
	t_minishell	*mini;

	mini = ft_calloc(1, sizeof(t_minishell));
	if (!mini)
		return (NULL);
	if (!create_env(mini, envp))
		return (safe_free(mini), NULL);
	if (getcwd(mini->pwd, BUFFER_SIZE) == NULL)
		mini->pwd[0] = '\0';
	if (!add_dico(mini->env, "?", "0"))
		return (free_dico(&mini->env), safe_free(mini), NULL);
	if (envp && getenv("SHLVL"))
	{
		v = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
		if (!v || !add_dico(mini->env, "SHLVL", v))
			return (safe_free(v), free_dico(&mini->env), safe_free(mini), NULL);
	}
	mini->paths = NULL;
	mini->hd_path = ft_strjoin(mini->pwd, "/.hd");
	if (!mini->hd_path)
	{
		ft_free_split(mini->paths);
		return (safe_free(v), free_dico(&mini->env), safe_free(mini), NULL);
	}
	return (safe_free(v), mini);
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

static t_dico	*create_env(t_minishell *mini, char **envp)
{
	if (*envp)
		mini->env = array_dico(envp);
	else
		mini->env = init_dico(NULL, NULL);
	return (mini->env);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*mini;
	int			exit_code;

	(void)av;
	if (ac > 1)
		return (ft_putstr_fd("minishell: wrong arguments amount\n", STDERR));
	setup_signals(handler);
	mini = init_minishell(envp, NULL);
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
	return (exit_code = mini->exit_code, free_mini(&mini), exit_code);
}
