/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:38 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/11 16:08:54 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "error.h"
#include "libft/libft.h"

static int	treat_redirections(char *fname, t_delim delim, int *in, int *out);

int	check_paths(t_minishell *mini, t_cmd *cmd)
{
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	if (!mini->paths)
		return (ERR_PARSING);
	while (mini->paths[i])
	{
		temp = ft_strjoin(mini->paths[i], "/");
		if (!temp)
			return (mini->exit = ERR_ALLOC, ERR_ALLOC);
		path = ft_strjoin(temp, cmd->fname);
		safe_free(temp);
		if (!path)
			return (mini->exit = ERR_ALLOC, ERR_ALLOC);
		if (access(path, F_OK) == 0)
			return (cmd->path = path, GOOD);
		safe_free(path);
		i++;
	}
	return (cmd->path = NULL, GOOD);
}

/* Open each files and store the last fd for in and out inside cmd */
int	redirections(t_cmd *cmd)
{
	int	i;
	int	fd_in;
	int	fd_out;

	i = 0;
	fd_out = -1;
	fd_in = -1;
	while (cmd->delim_f != NULL && cmd->delim_f[i] != NULL)
	{
		if (fd_in > 0)
			closef(fd_in, 0);
		if (fd_out > 0)
			closef(fd_out, 0);
		if (treat_redirections(cmd->delim_f[i], cmd->delim[i], &fd_in, &fd_out))
			return (ERR_FILES);
		i++;
	}
	if (cmd->delim && cmd->delim[i - 1] == IN_NL)
	{
		cmd->heredoc = fd_in;
		cmd->in = closef(cmd->in, fd_out);
	}
	else
	{
		if (fd_in > 0)
			cmd->in = closef(cmd->in, fd_in);
		if (fd_out > 0)
			cmd->out = closef(cmd->out, fd_out);
	}
	return (0);
}

static int	treat_redirections(char *fname, t_delim delim, int *in, int *out)
{
	int	pip[2];

	if (delim == IN)
	{
		*in = open(fname, O_RDWR, S_IRUSR | S_IWUSR);
		if (*in < 0)
			return (perror("minishell"), ERR_FILES);
	}
	else if (delim == OUT)
	{
		*out = open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
		if (*out < 0)
			return (perror("minishell"), ERR_FILES);
	}
	else if (delim == OUT_APPEND)
	{
		*out = open(fname, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
		if (*out < 0)
			return (perror("minishell"), ERR_FILES);
	}
	else if (delim == IN_NL)
	{
		if (pipe(pip) < 0)
			return (perror2("minishell:",">>"), ERR_CMD_PIPE);
		*in = pip[1];
		*out = pip[0];
	}
	return (0);
}

int	here_doc(char *stop, int fd, int is_last)
{
	char	*buf;

	buf = get_next_line(STDIN);
	while (buf && ft_strncmp(buf, stop, ft_strlen(stop)))
	{
		if (is_last)
			write(fd, buf, ft_strlen(buf));
		safe_free(buf);
		buf = get_next_line(STDIN);
	}
	safe_free(buf);
}