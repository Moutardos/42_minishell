/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:42:56 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/26 14:27:03 by lcozdenm         ###   ########.fr       */
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
	int		re;

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
		if (cmd->fname)
			re = treat_cmds(cmd, mini);
		if (re < 0)
			return (close_pipe(mini->cmds, -1), exit_m(mini, NULL), -1);
		if (re == 1)
			ft_printf("minishell: command not found : %s\n", cmd->fname);
		cmd = cmd->next;
	}
	close_pipe(mini->cmds, -1);
	if (wait_exec(mini) < 0)
		return (exit_m(mini, NULL), -1);
	return (0);
}

static int	treat_cmds(t_cmd *cmd, t_minishell *mini)
{
	pid_t	pid;
	char	**env;

	if (!cmd->path && cmd->builtin == B_NONE)
		return (1);
	if (cmd->path && access(cmd->path, F_OK))
		return (perror2("minishell : ", cmd->path), 1);
	if (cmd->builtin != B_NONE && !cmd->next)
	{
		if (treat_builtins(mini, cmd) < 0)
			return (printf("minishell: error builtin"), -1);
		return (0);
	}
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
		if (cmd->builtin != B_NONE)
		{
			if (treat_builtins(mini, cmd) < 0)
				return (ft_free_split(env), -1);
			return (-1);
		}
		execve(cmd->path, cmd->av, env);
		return (ft_free_split(env), perror2("minishell", cmd->path), -1);
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
			return (-1);
		current = current->next;
		i++;
	}
	return (0);
}

static int	treat_builtins(t_minishell *mini, t_cmd *cmd)
{
	int		re;
	char	*str;

	re = 1;
	if (cmd->builtin == ECHO)
		re = echo(cmd);
	else if (cmd->builtin == PWD)
		re = pwd(mini, cmd->out);
	else if (cmd->builtin == CD)
		re = cd(mini, cmd);
	else if (cmd->builtin == ENV)
	{
		re = 0;
		display_dico(mini->env);
	}
	else if (cmd->builtin == EXPORT)
		re = export_m(mini, cmd);
	else if (cmd->builtin == UNSET)
		re = unset(mini, cmd);
	else if (cmd->builtin == EXIT)
		re = exit_m(mini, cmd);
	str = ft_itoa(re);
	if (!str || !add_dico(mini->env, "?", str))
		return (exit_m(mini, NULL), -1);
	return (re);
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
