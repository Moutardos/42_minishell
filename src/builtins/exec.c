/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:42:56 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/09 16:46:58 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "error.h"
#include "builtins.h"
static t_error	treat_cmds(t_cmd *cmds, char **env);
static t_error	create_pipe(t_cmd *cmds);
static void		close_pipe(t_cmd *cmds, int n);
static int is_last_heredoc(t_cmd *cmd, int i);
static int	treat_builtins(t_cmd *cmds, char **env);

/// @brief  Execute each commands 1 by 1
/// @param  cmds linked list of commands
/// @return error nb 
int	execute(t_minishell	*mini)
{
	const char	*fname;
	t_error		err;
	t_cmd		*curr;

	err = create_pipe(mini->cmds);
	if (err)
		return (err);
	curr = mini->cmds;
	while (curr != NULL)
	{
		curr->fname = curr->av[0];
		if (curr->path == NULL)
			if (check_paths(mini, curr))
				return (close_pipe(mini->cmds, -1), ERR_ALLOC);
		err = treat_cmds(curr, NULL);
		closef(curr->in, 0);
		closef(curr->out, 0);
		closef(curr->heredoc, 0);
		if (err)
			return (close_pipe(mini->cmds, -1), err);
		curr = curr->next;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}

static t_error	treat_cmds(t_cmd *cmds, char **env)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		i;

	cmd = cmds;
	i = 0;
	while (cmd->delim_f[i] != NULL)
	{
		if (cmd->delim[i] == IN_NL)
			here_doc(cmd->delim_f[i], cmd->heredoc, is_last_heredoc(cmd, i +1));
		i++;
	}
	if (!treat_builtins(cmds, env))
		return (0);
	pid = fork();
	if (pid == F_CHILD)
	{
		if (dup2(cmd->in, STDIN) < 0)
			return (perror("minishell: in"), 0);
		if (dup2(cmd->out, STDOUT) < 0)
			return (perror("minishell: out"), 0);
		close_pipe(cmd, -1);
		execve(cmd->path, cmd->av, env);
		return (perror2("minishell : ", cmd->path), ERR_CMD_FAIL);
	}
	return (GOOD);
}

/// @brief  Pipe each command after treating each redirections
/// @param  cmds linked list of commands
/// @return error nb 
static t_error	create_pipe(t_cmd *cmds)
{
	t_cmd	*current;
	int		i;
	int		pip[2];

	i = 0;
	current = cmds;
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			if (pipe(pip) < 0)
				return (close_pipe(cmds, i), perror("minishell"), ERR_CMD_PIPE);
			current->out = pip[1];
			current->next->in = pip[0];
		}
		if (redirections(current) < 0)
			return (perror("minishell"), ERR_FILES);
		current = current->next;
		i++;
	}
	return (GOOD);
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
		closef(current->heredoc, 0);
		i++;
		current = current->next;
	}
}

static int is_last_heredoc(t_cmd *cmd, int i)
{
	while (cmd->delim_f[i] != NULL)
	{
		if (cmd->delim[i] == IN_NL)
			return (0);
		i++;
	}
	return (1);
}

static int	treat_builtins(t_cmd *cmds, char **env)
{
	if (!ft_strcmp(cmds->fname, "echo"))
		return (echo(cmds));
	return (1);
	//todo le reste
}