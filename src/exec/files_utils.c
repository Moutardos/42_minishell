/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:38 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/21 15:07:27 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft/libft.h"
#include "utils.h"
#include "builtins.h"

int	check_paths(t_minishell *mini, t_cmd *cmd)
{
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	if (!mini->paths || !ft_strcmp(cmd->fname, ""))
		return (-1);
	while (mini->paths[i])
	{
		temp = ft_strjoin(mini->paths[i], "/");
		if (!temp)
			return (exit_m(mini, NULL), -1);
		path = ft_strjoin(temp, cmd->fname);
		safe_free(temp);
		if (!path)
			return (exit_m(mini, NULL), -1);
		if (access(path, F_OK) == 0)
			return (cmd->path = path, 0);
		safe_free(path);
		i++;
	}
	ft_printf("minishell: %s: not found\n", cmd->fname);
	return (cmd->path = NULL, 0);
}

int	closef(int fd, int new)
{
	if (fd != STDIN && fd != STDOUT && fd > 0)
		close(fd);
	return (new);
}

int	is_last_heredoc(t_cmd *cmd, int i)
{
	if (cmd->delim[i] != IN_NL)
		return (0);
	i++;
	while (cmd->delim_f[i] && cmd->delim[i] != IN_NL)
		i++;
	if (!cmd->delim_f[i])
		return (1);
	return (0);
}

void	close_pipe(t_cmd *cmds, int n)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = cmds;
	while (current->prev != NULL)
		current = current->prev;
	while (((n > 0 && i < n) || (n < 0)) && current != NULL)
	{
		closef(current->in, 0);
		closef(current->out, 0);
		i++;
		current = current->next;
	}
}
