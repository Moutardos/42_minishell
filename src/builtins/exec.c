/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:42:56 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/12 14:41:13 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "error.h"

static t_error	treat_cmds(t_cmd *cmds, char **env);
static t_error	create_pipe(t_cmd *cmds);
static void		close_pipe(t_cmd *cmds, int n);

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
		if (curr->ac < 1)
			//jsp encore
			;
		curr->fname = curr->av[0];
		if (check_paths(mini, curr))
			return (ERR_ALLOC);
		err = treat_cmds(curr, NULL);
		close(curr->in);
		close(curr->out);
		if (err)
			return (err);
		curr = curr->next;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}

/// @brief  Execute the first command,  if there's another command in cmds,
///         pipe its output to the input of the next one.
/// @param  cmds linked list of commands
/// @return error nb 
/// @todo   check for builtin
// static t_error	treat_cmds(t_cmd *cmds, char **env)
// {
// 	pid_t	pid;
// 	t_cmd	*cmd;

// 	cmd = cmds;
// 	pid = fork();
// 	if (pid == F_CHILD)
// 	{
// 		if (cmd->prev != NULL)
// 		{
// 			if (dup2(cmd->in, STDIN) < 0)
// 				return (perror("minishell: in"), 0);
// 			close(cmd->in);
// 		}
// 		if (cmd->next != NULL)
// 		{
// 			if (dup2(cmd->next->out, STDOUT) < 0)
// 				return (perror("minishell: out"), 0);
// 			close(cmd->next->out);
// 		}
// 		execve(cmd->path, cmd->av, env);
// 		return (perror("minishell: execution:"), 0);
// 	}
// 	return (GOOD);
// }

static t_error	treat_cmds(t_cmd *cmds, char **env)
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
				return (perror("minishell: in"), 0);
		}
		if (cmd->next != NULL)
		{
			if (dup2(cmd->next->out, STDOUT) < 0)
				return (perror("minishell: out"), 0);
		}
		close_pipe(cmd, -1);
		execve(cmd->path, cmd->av, env);
		return (perror("minishell: execution:"), 0);
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
	while (current->next != NULL)
	{
		// if (redirections(current) < 0)
		// 	return (perror("minishell"), ERR_FILES);
		if (pipe(pip) < 0)
			return (close_pipe(cmds, i), perror("minishell"), ERR_CMD_PIPE);
		current->out = pip[0];
		current->in = pip[1];
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
	while(current->prev == NULL)
	{
		current = current->prev;
	}
	while (((n > 0 && i < n) || (n < 0)) && current != NULL)
	{
		close(current->in);
		close(current->out);
		i++;
		current = current->next;
	}
}
