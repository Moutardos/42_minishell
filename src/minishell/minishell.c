/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:37:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/13 21:54:09 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "exec.h"

/// @brief Minishell struct and fields init
/// @return Newly allocated shell entity
t_minishell	*init_minishell(char **envp)
{
	t_minishell *mini;
	char		*path;
	
	path = getenv("PATH");
	if (!path)
		return (NULL);
	mini = ft_calloc(1, sizeof(t_minishell));
	if (!mini)
		return (NULL);
	if (!envp)
		mini->env = NULL;
	else
		mini->env = array_dico(envp);
	if (getcwd(mini->pwd, BUFFER_SIZE) == NULL)
	{
		perror("minishell");
		return (free_dico(&mini->env), safe_free(mini), NULL);
	}
	//paths par defaut 
	mini->paths = ft_split(path, ':');
	if (!mini->paths)
	{
		perror("minishell");
		return (, free_dico(&mini->env), safe_free(mini), NULL);
	}
	mini->exit = -1;
	//Ajouter ici par la suite les fieds a allouer / initialiser
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
	free(curr);
	*mini = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*mini;

	(void)ac;
	(void)av;
	mini = init_minishell(envp);
	if (!mini)
		return (-1);
	while (mini->exit == -1)
	{
		if (parse_current_cmd(mini) < 0)
			break ;
		if (mini->cmds)
		{
			execute(mini);
			free_cmds(&mini->cmds);
		}
		test++;
	}
	free_mini(&mini);
}
