/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:38 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/15 18:48:30 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft/libft.h"
#include "utils.h"

static int	treat_redirections(char *fname, t_delim delim, int *in, int *out);
static int	here_doc(char *stop, t_dico *env, int fd, int is_last);

int	check_paths(t_minishell *mini, t_cmd *cmd)
{
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	if (!mini->paths)
		return (-1);
	while (mini->paths[i])
	{
		temp = ft_strjoin(mini->paths[i], "/");
		if (!temp)
			return (mini->exit = -1, -1);
		path = ft_strjoin(temp, cmd->fname);
		safe_free(temp);
		if (!path)
			return (mini->exit = -1, -1);
		if (access(path, F_OK) == 0)
			return (cmd->path = path, 0);
		safe_free(path);
		i++;
	}
	return (cmd->path = NULL, 0);
}

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
		if (is_last_heredoc(cmd, i))
			fname = mini->hd_path;
		else if (cmd->delim[i] == IN_NL)
			continue;
		else
			fname = cmd->delim_f[i];
		if (treat_redirections(fname, cmd->delim[i], &in, &out) < 0)
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

	if (delim == IN)
	{
		*in = open(fname, O_RDWR, S_IRUSR | S_IWUSR);
		if (*in < 0)
			return (perror("minishell"), 1);
	}
	else if (delim == OUT)
	{
		*out = open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
		if (*out < 0)
			return (perror("minishell"), 1);
	}
	else if (delim == OUT_APPEND)
	{
		*out = open(fname, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
		if (*out < 0)
			return (perror("minishell"), 1);
	}
	else if (delim == IN_NL)
	{
		*in = open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
		if (*in < 0)
			return (perror("minishell"), 1);
	}
	return (0);
}

int	treating_here_doc(t_cmd *cmd, t_minishell *mini)
{
	int		i;
	int		check;
	int		is_last;

	i = 0;
	while (cmd->delim_f[i])
	{
		if (cmd->delim[i] == IN_NL)
		{
			is_last = is_last_heredoc(cmd, i);
			if (here_doc(cmd->delim_f[i], mini->env, cmd->in, is_last) < 0)
				return (-1);
			closef(cmd->in, 0);
			cmd->in = open(mini->hd_path, O_RDWR, S_IRUSR | S_IWUSR);
			if (cmd->in < 0)
				return (perror("minishell"), -1);
		}
		i++;
	}
	return (0);
}

static int	here_doc(char *stop, t_dico *env, int fd, int is_last)
{
	char	*buf;
	char	*str;

	ft_printf("heredoc> ");
	buf = get_next_line(STDIN);
	if (!buf)
		return (-1);
	str = replace_str2(env, buf);
	if (!str)
		return (safe_free(buf), -1);
	while (str && ft_strncmp(str, stop, ft_strlen(str) - 1))
	{
		if (is_last)
			write(fd, str, ft_strlen(str));
		safe_free(buf);
		ft_printf("heredoc> ");
		buf = get_next_line(STDIN);
		if (!buf)
			return (-1);
		str = replace_str2(env, buf);
		if (!str)
			return (safe_free(buf), -1);
	}
	safe_free(buf);
	close(fd);
	return (0);
}
