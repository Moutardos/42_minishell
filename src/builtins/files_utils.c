/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:38 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/08 17:36:55 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "error.h"
#include "libft/libft.h"
static int	treat_redirections(char *fname, t_delim delim, int *in, int *out);

int	check_paths(t_minishell *mini, t_cmd *cmd)
{
	char	*path;
	int		i;

	i = 0;
	if (!mini->paths)
		return (ERR_PARSING);
	while (mini->paths[i])
	{
		path = ft_strjoin(mini->paths[i], cmd->fname);
		if (!path)
			return (mini->exit = ERR_ALLOC, ERR_ALLOC);
		if (access(path, F_OK) == 0)
			return (cmd->path = path, GOOD);
		safe_free(path);
		i++;
	}
	path = ft_strjoin(".",cmd->fname);
	// path = ft_strjoin(mini->pwd, cmd->fname);
	if (!path)
		return (mini->exit = ERR_ALLOC, ERR_ALLOC);
	return (cmd->path = path, GOOD);
}
/* Open each files and store the last fd for in and out inside cmd */
int	redirections(t_cmd *cmd)
{
	int	i;
	int fd_in;
	int	fd_out;

	if (!cmd->delim || !cmd->delim_f)
		return (0);
	i = 0;
	fd_out = -1;
	fd_in = -1;
	while (cmd->delim_f[i] != NULL)
	{
		if (fd_in > 0)
			close(fd_in);
		if (fd_out > 0)
			close(fd_out);
		if (!treat_redirections(cmd->delim_f[i], cmd->delim[i], &fd_in, &fd_out))
			return (ERR_FILES);
	}
	if (fd_in > 0)
		cmd->in = fd_in;
	if (fd_out > 0)
		cmd->out = fd_out;
	return (0);

}

static int	treat_redirections(char *fname, t_delim delim, int *in, int *out)
{
	if (delim == IN)
	{
		*in = open(fname, O_RDWR, S_IRUSR | S_IWUSR);
		if (*in < 0)
			return(perror("minishell"), ERR_FILES);
	}
	else if (delim == OUT)
	{
		*out = open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
		if (*out < 0)
			return(perror("minishell"), ERR_FILES);
	}
	else if (delim == OUT_APPEND)
	{
		*out = open(fname, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
		if (*out < 0)
			return(perror("minishell"), ERR_FILES);
	}
	else if (delim == IN_NL)
	{
		//TODO heredoc
	}
	return (0);
}