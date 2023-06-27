/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:10:16 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/27 14:48:25 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

t_cmd	*cmd_last(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*temp;

	if (new)
	{
		if (*cmd)
		{
			temp = cmd_last(*cmd);
			temp->next = new;
		}
		else
			*cmd = new;
	}
}

void	cmd_del_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd->av[i] != NULL)
	{
		safe_free(cmd->av[i]);
		i++;
	}
	safe_free(cmd->av);
	i = -1 ;
	while (i++ < cmd->delim_a - 1)
		safe_free(cmd->delim_f[i]);
	safe_free(cmd->delim_f);
	safe_free(cmd->delim);
	safe_free(cmd);
}

void	cmd_del_last(t_cmd *cmd)
{
	t_cmd	*head;
	t_cmd	*head_min_one;

	head = cmd;
	head_min_one = head;
	while (head->next != NULL)
	{
		head_min_one = head;
		head = head->next;
	}
	head_min_one->next = NULL;
	cmd_del_cmd(head);
}
