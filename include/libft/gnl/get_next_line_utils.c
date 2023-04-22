/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 07:50:33 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/01/30 15:04:17 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd	*get_new_fd(int fd, t_ffd **fdinfo)
{
	t_fd	*node;
	ssize_t	i;

	node = (*fdinfo)->first;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = malloc(sizeof(t_fd));
	if (!node)
		return (NULL);
	i = -1;
	while (++i <= BUFFER_SIZE)
		node->reste[i] = '\0';
	node->fd = fd;
	if (!(*fdinfo)->first)
		node->next = NULL;
	else
		node->next = (*fdinfo)->first;
	(*fdinfo)->first = node;
	return (node);
}

void	free_fd(int fd, t_ffd **fd_infos)
{
	t_fd	*c;
	t_fd	*node;

	c = (*fd_infos)->first;
	if (c->fd == fd)
	{
		node = c->next;
		if (node)
			(*fd_infos)->first = node;
		else
		{
			free(*fd_infos);
			*fd_infos = NULL;
		}
		return (free_line(&c->lines), free(c));
	}
	node = (*fd_infos)->first;
	c = node->next;
	while (c)
	{
		if (c->fd == fd)
			return (node->next = c->next, free_line(&c->lines), free(c));
		c = c->next;
		node = node->next;
	}
}

void	free_line(t_line **line)
{
	t_line	*node;
	t_line	*curr;

	if (*line == NULL)
		return ;
	curr = *line;
	while (curr)
	{
		node = curr->next;
		free(curr);
		curr = node;
	}
	*line = NULL;
}

ssize_t	ft_strchr2(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}

void	fill_reste(t_fd *fdinfo, t_line *line)
{
	ssize_t	offset;
	size_t	i;

	i = 0;
	offset = ft_strchr2(line->buf, '\n');
	if (offset == -1)
		while (fdinfo->reste[i] != '\0')
			fdinfo->reste[i++] = '\0';
	else
	{
		while (line->buf[offset + i + 1] != '\0')
		{
			fdinfo->reste[i] = line->buf[offset + i + 1];
			i++;
		}
		while (fdinfo->reste[i] != '\0')
			fdinfo->reste[i++] = '\0';
	}
}
