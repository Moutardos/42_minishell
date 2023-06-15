/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:42:56 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/15 18:59:58 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "builtins.h"
#include "utils.h"

static int	treat_cmds(t_cmd *cmds, t_minishell *mini);
static int	create_pipe(t_minishell *mini);
static void	close_pipe(t_cmd *cmds, int n);
static int	treat_builtins(t_minishell *mini, t_cmd *cmds, char **env);

/// @brief  Execute each commands 1 by 1
/// @param  cmds linked list of commands
/// @return error nb 
int	execute(t_minishell	*mini)
{
	t_cmd		*curr;
	int			status;
	char		*re;

	if (create_pipe(mini) < 0)
		return (-1);
	curr = mini->cmds;
	while (curr != NULL)
	{
		if (curr->path == NULL && curr->fname)
			if (check_paths(mini, curr))
				return (close_pipe(mini->cmds, -1), -1);
		if (treat_cmds(curr, mini) < 0)
			return (close_pipe(mini->cmds, -1), -1);
		closef(curr->in, 0);
		closef(curr->out, 0);
		curr = curr->next;
	}
	while (waitpid(-1, &status, NULL) > 0)
	{
		if (WIFEXITED(status))
		{
			re = ft_itoa(WEXITSTATUS(status));
			if (!re)
				return (-1);
			add_dico(mini->env, "?", re);
			safe_free(re);
		}
	}
	return (0);
}

static int	treat_cmds(t_cmd *cmd, t_minishell *mini)
{
	pid_t	pid;
	char	**env;

	env = dico_array(mini->env);
	if (!env)
		return (-1);
	if (!cmd->av)
		return (0);
	if (treating_here_doc(cmd, mini) < 0)
			return (-1);
	if (!treat_builtins(mini, cmd, env))
		return (ft_free_split(env), 0);
	pid = fork();
	if (pid == F_CHILD)
	{
		if (dup2(cmd->in, STDIN) < 0)
			return (perror("minishell: in"), 0);
		if (dup2(cmd->out, STDOUT) < 0)
			return (perror("minishell: out"), 0);
		close_pipe(cmd, -1);

		execve(cmd->path, cmd->av, env);
		return (ft_free_split(env), perror2("minishell : ", cmd->path), 0);
	}
	return (ft_free_split(env), 0);
}

/// @brief  Pipe each command after treating each redirections
/// @param  cmds linked list of commands
/// @return error nb 
static int	create_pipe(t_minishell *mini)
{
	t_cmd	*current;
	int		i;
	int		pip[2];

	i = 0;
	current = mini->cmds;
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			if (pipe(pip) < 0)
				return (close_pipe(mini->cmds, i), perror("minishell"), -1);
			current->out = pip[1];
			current->next->in = pip[0];
		}
		if (redirections(mini, current) < 0)
			return (perror("minishell"), -1);
		current = current->next;
		i++;
	}
	return (0);
}

/// @brief  Close pipes in the range of n
/// @param  cmds linked list of commands
/// @param  n    range, max if negative  
static void	close_pipe(t_cmd *cmds, int n)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = cmds;
	while (current->prev != NULL)
		current = current->prev;
	while (((n > 0 && i < n) || (n < 0)) && current != NULL)
	{
		closef(current->in, 0);
		closef(current->out, 0);
		i++;
		current = current->next;
	}
}

static int	treat_builtins(t_minishell *mini, t_cmd *cmd, char **env)
{
	if (!ft_strcmp(cmd->fname, "echo"))
		return (echo(cmd));
	else if (!ft_strcmp(cmd->fname, "pwd"))
		return (pwd(mini, cmd->out));
	else if (!ft_strcmp(cmd->fname, "cd"))
		return (cd(mini));
	else if (!ft_strcmp(cmd->fname, "env"))
		return (display_dico(mini->env), 0);
	else if (!ft_strcmp(cmd->fname, "export"))
		return (export_m(mini, cmd));
	else if (!ft_strcmp(cmd->fname, "unset"))
		return (unset(mini, cmd));
	else if (!ft_strcmp(cmd->fname, "exit"))
		return (exit_m(mini));
	return (1);
}
