/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:10:16 by coltcivers        #+#    #+#             */
/*   Updated: 2023/05/05 16:50:09 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char *delim)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->next = NULL;
	cmd->delim_f = delim;
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

t_cmd	*cmd_first(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->prev != NULL)
		lst = lst->next;
	return (lst);
}

void	cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*temp;

	if (*cmd)
	{
		temp = cmd_last(*cmd);
		temp->next = new;
	}
	else
		*cmd = new;
}

void	cmd_del_last(t_cmd **cmd)
{
	t_cmd *	head;
	t_cmd *	head_min_one;

	head = *cmd;
	while (head->next != NULL)
	{
		head_min_one = head;
		head = head->next;
	}
	head_min_one->next = NULL;
	free(head);
}