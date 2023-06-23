/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:15:16 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/23 18:04:48 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "utils.h"
#include "builtins.h"

static int	t_redirections(char *name, t_cmd *cmd, t_delim d, int f[2]);
static int	here_doc(char *stop, t_minishell *mini, int fd, int is_last);
static char	*prompt_heredoc(t_minishell *mini);

/* Open each files and store the last fd for in and out inside cmd */
int	redirections(t_minishell *mini, t_cmd *cmd)
{
	int		i;
	int		fds[2];
	char	*fname;

	i = -1;
	fds[0] = -1;
	fds[1] = -1;
	while (cmd->delim_f != NULL && cmd->delim_f[++i] != NULL)
	{
		fname = NULL;
		if (cmd->delim[i] != IN_NL)
			fname = cmd->delim_f[i];
		else if (is_last_heredoc(cmd, i))
			fname = mini->hd_path;
		if (fname)
			if (t_redirections(fname, cmd, cmd->delim[i], fds) < 0)
				return (-1);
	}
	if (fds[0] > 0)
		cmd->in = closef(cmd->in, fds[0]);
	if (fds[1] > 0)
		cmd->out = closef(cmd->out, fds[1]);
	return (0);
}

static int	t_redirections(char *name, t_cmd *cmd, t_delim d, int f[2])
{
	int	option;

	if (d == IN || d == IN_NL)
	{
		closef(f[0], 0);
		if (d == IN)
			option = O_RDWR;
		else
			option = O_CREAT | O_RDWR | O_TRUNC;
		f[0] = open(name, option, S_IRUSR | S_IWUSR);
		if (f[0] < 0)
			return (perror("minishell"), 1);
	}
	else if (d == OUT || d == OUT_APPEND)
	{
		closef(f[1], 0);
		if (d == OUT)
			option = O_CREAT | O_RDWR | O_TRUNC;
		else
			option = O_CREAT | O_RDWR | O_APPEND;
		f[1] = open(name, option, S_IRUSR | S_IWUSR);
		if (f[1] < 0)
			return (perror("minishell"), 1);
	}
	return (0);
}

int	treating_here_doc(t_cmd *cmd, t_minishell *mini)
{
	int		i;
	int		is_last;

	i = 0;
	while (cmd->delim_f[i])
	{
		if (cmd->delim[i] == IN_NL)
		{
			is_last = is_last_heredoc(cmd, i);
			if (here_doc(cmd->delim_f[i], mini, cmd->in, is_last) < 0)
				return (-1);
			cmd->in = open(mini->hd_path, O_RDWR, S_IRUSR | S_IWUSR);
			if (cmd->in < 0)
				return (perror("minishell"), -1);
		}
		i++;
	}
	return (0);
}

static int	here_doc(char *stop, t_minishell *mini, int fd, int is_last)
{
	char	*str;

	str = prompt_heredoc(mini);
	while (str && ft_strcmp(str, stop))
	{
		if (is_last)
		{
			ft_putstr_fd(str, fd);
			ft_putchar_fd('\n', fd);
		}
		safe_free(str);
		str = prompt_heredoc(mini);
	}
	return (close(fd), 0);
}

static char	*prompt_heredoc(t_minishell *mini)
{
	char	*buf;
	char	*str;

	buf = readline("heredoc>");
	if (!buf)
		return (NULL);
	str = replace_str2(mini->env, buf);
	if (!str)
		return (exit_m(mini, NULL), NULL);
	return (str);
}
