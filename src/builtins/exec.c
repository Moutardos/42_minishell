/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:42:56 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/04 19:07:25 by lcozdenm         ###   ########.fr       */
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
			if (dup2(cmd->in, STDIN) < 0)
				return (perror("minishell:"), 0);
			close(cmd->in);
		}
		if (cmd->next != NULL)
		{
			if (dup2(cmd->next->out, STDOUT) < 0)
				return (perror("minishell:"), 0);
			close(cmd->next->out);
		}
		close(cmd->out);
		execve(cmd->av[0], cmd->av, NULL);
		return (perror("minishell:"), 0);
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
	int		pip[2];


	i = 0;
	current = cmds;
	while (current != NULL)
	{

		if (pipe(pip) < 0)
		{
			close_pipe(cmds, i);
			return (ERR_CMD_PIPE);
		}
		cmds->out = pip[0];
		cmds->in = pip[1];
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
		close(current->in);
		close(current->out);
		i++;
		current = current->next;
	}
}
