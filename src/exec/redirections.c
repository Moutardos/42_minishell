/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:15:16 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/21 14:32:02 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "utils.h"
#include "builtins.h"

static int	treat_redirections(char *fname, t_delim delim, int *in, int *out);
static int	here_doc(char *stop, t_minishell *mini, int fd, int is_last);
static char	*prompt_heredoc(t_minishell *mini);

/* Open each files and store the last fd for in and out inside cmd */
int	redirections(t_minishell *mini, t_cmd *cmd)
{
	int		i;
	int		in;
	int		out;
	char	*fname;

	i = -1;
	out = -1;
	in = -1;
	while (cmd->delim_f != NULL && cmd->delim_f[++i] != NULL)
	{
		closef(in, 0);
		closef(out, 0);
		fname = NULL;
		if (cmd->delim[i] != IN_NL)
			fname = cmd->delim_f[i];
		else if (is_last_heredoc(cmd, i))
			fname = mini->hd_path;
		if (fname && treat_redirections(fname, cmd->delim[i], &in, &out) < 0)
			return (-1);
	}
	if (in > 0)
		cmd->in = closef(cmd->in, in);
	if (out > 0)
		cmd->out = closef(cmd->out, out);
	return (0);
}

static int	treat_redirections(char *fname, t_delim delim, int *in, int *out)
{
	int	option;

	if (delim == IN || delim == IN_NL)
	{
		if (delim == IN)
			option = O_RDWR;
		else
			option = O_CREAT | O_RDWR | O_TRUNC;
		*in = open(fname, option, S_IRUSR | S_IWUSR);
		if (*in < 0)
			return (perror("minishell"), 1);
	}
	else if (delim == OUT || delim == OUT_APPEND)
	{
		if (delim == OUT)
			option = O_CREAT | O_RDWR | O_TRUNC;
		else
			option = O_CREAT | O_RDWR | O_APPEND;
		*out = open(fname, option, S_IRUSR | S_IWUSR);
		if (*out < 0)
			return (perror("minishell"), 1);
	}
	return (0);
}

int	treating_here_doc(t_cmd *cmd, t_minishell *mini)
{
	int		i;
	int		is_last;
	char	*stop;

	i = 0;
	while (cmd->delim_f[i])
	{
		if (cmd->delim[i] == IN_NL)
		{
			is_last = is_last_heredoc(cmd, i);
			stop = ft_strjoin(cmd->delim_f[i], "\n");
			if (!stop)
				return (perror("minishell"), -1);
			if (here_doc(stop, mini, cmd->in, is_last) < 0)
				return (safe_free(stop), -1);
			safe_free(stop);
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
			ft_putstr_fd(str, fd);
		safe_free(str);
		str = prompt_heredoc(mini);
	}
	return (close(fd), 0);
}

static char	*prompt_heredoc(t_minishell *mini)
{
	char	*buf;
	char	*str;

	ft_printf("heredoc> ");
	buf = get_next_line(STDIN);
	if (!buf)
		return (NULL);
	str = replace_str2(mini->env, buf);
	if (!str)
		return (exit_m(mini, NULL), NULL);
	return (str);
}
