/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:42:56 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/22 19:54:47 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "builtins.h"
#include "utils.h"

static int	treat_cmds(t_cmd *cmds, t_minishell *mini);
static int	create_pipe(t_minishell *mini);
static int	treat_builtins(t_minishell *mini, t_cmd *cmds);
static int	wait_exec(t_minishell *mini);

/// @brief  Execute each commands 1 by 1
/// @param  cmds linked list of commands
/// @return error nb 
int	execute(t_minishell	*mini)
{
	t_cmd	*cmd;

	cmd = mini->cmds;
	if (create_pipe(mini) < 0)
		return (-1);
	while (cmd != NULL)
	{
		if (cmd->path == NULL && cmd->fname)
			if (check_paths(mini, cmd))
				return (close_pipe(mini->cmds, -1), -1);
		if (treating_here_doc(cmd, mini) < 0)
			return (exit_m(mini, NULL), -1);
		if (cmd->fname && treat_cmds(cmd, mini) < 0)
			return (close_pipe(mini->cmds, -1), -1);
		closef(cmd->in, 0);
		closef(cmd->out, 0);
		cmd = cmd->next;
	}
	if (wait_exec(mini) < 0)
		return (exit_m(mini, NULL), -1);
	return (0);
}

static int	treat_cmds(t_cmd *cmd, t_minishell *mini)
{
	pid_t	pid;
	char	**env;

	if (!treat_builtins(mini, cmd))
		return (0);
	if (!cmd->path)
		return (0);
	pid = fork();
	if (pid == F_CHILD)
	{
		env = dico_array(mini->env);
		if (!env)
			return (-1);
		if (dup2(cmd->in, STDIN) < 0)
			return (perror("minishell: in"), 0);
		if (dup2(cmd->out, STDOUT) < 0)
			return (perror("minishell: out"), 0);
		close_pipe(cmd, -1);
		execve(cmd->path, cmd->av, env);
		return (ft_free_split(env), perror2("minishell : ", cmd->path), 0);
	}
	return (0);
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

static int	treat_builtins(t_minishell *mini, t_cmd *cmd)
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
		return (exit_m(mini, cmd));
	return (1);
}

static int	wait_exec(t_minishell *mini)
{
	int			status;
	char		*re;
	t_dico		*check;
	extern int	g_exit_code;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
		{
			g_exit_code = WEXITSTATUS(status);
			re = ft_itoa(WEXITSTATUS(status));
			if (!re)
				return (-1);
			check = add_dico(mini->env, "?", re);
			if (!check)
				return (safe_free(re), -1);
			safe_free(re);
		}
	}
	return (0);
}
