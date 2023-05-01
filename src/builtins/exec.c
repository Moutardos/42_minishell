/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:42:56 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/01 13:18:11 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "error.h"

static t_error	treat_cmds(t_cmd *cmds);
static t_error	create_pipe(t_cmd *cmds);
static void		close_pipe(t_cmd *cmds, int n);

/// @brief  Execute each commands 1 by 1
/// @param  cmds linked list of commands
/// @return error nb 
int	execute(t_cmd	*cmds)
{
	const char	*fname;
	t_error		err;
	t_cmd		*curr;

	err = create_pipe(cmds);
	if (err)
		return (err);
	curr = cmds;
	while (curr != NULL)
	{
		if (curr->ac < 1)
			return (ERR_CMD_NOARG);
		fname = curr->av[0];
		err = treat_cmds(curr);
		if (err)
		{
			return (err);
		}
		curr = curr->next;
	}
	while (wait(NULL) > 0)
		;
	close_pipe(cmds, -1);
	return (0);
}

/// @brief  Execute the first command,  if there's another command in cmds,
///         pipe its output to the input of the next one.
/// @param  cmds linked list of commands
/// @return error nb 
/// @todo   check for builtin
static t_error	treat_cmds(t_cmd *cmds)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = cmds;
	pid = fork();
	if (pid == F_CHILD)
	{
		if (cmd->prev != NULL)
		{
			if (dup2(cmd->pipe[0], STDIN) < 0)
				return (ERR_CMD_DUP0);
			close(cmd->pipe[0]);
		}
		if (cmd->next != NULL)
		{
			if (dup2(cmd->next->pipe[1], STDOUT) < 0)
				return (ERR_CMD_DUP1);
			close(cmd->next->pipe[1]);
		}
		execve(cmd->av[0], cmd->av, NULL);
		return (ERR_CMD_FAIL);
	}
	return (GOOD);
}

/// @brief  Pipe each command
/// @param  cmds linked list of commands
/// @return error nb 
static t_error	create_pipe(t_cmd *cmds)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = cmds;
	while (current != NULL)
	{
		if (pipe(current->pipe) < 0)
		{
			close_pipe(cmds, i);
			return (ERR_CMD_PIPE);
		}
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
	while ((n > 0 && i < n) && current != NULL)
	{
		close(current->pipe[0]);
		close(current->pipe[1]);
		i++;
		current = current->next;
	}
}
