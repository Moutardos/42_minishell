/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 06:59:27 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/01/30 14:58:53 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_ffd	*fdinfos = NULL;
	t_fd			*fdinfo;
	char			*res;
	ssize_t			size;

	if (fd < 0)
		return (NULL);
	fdinfos = init_fdinfos(fdinfos);
	if (!fdinfos)
		return (NULL);
	fdinfo = get_new_fd(fd, &fdinfos);
	if (!fdinfo)
		return (NULL);
	fdinfo->lines = fill_lines(fdinfo, &size);
	if (fdinfo->lines == NULL)
		return (free_fd(fd, &fdinfos), NULL);
	if (size == 0)
		return (free_fd(fd, &fdinfos), NULL);
	res = make_real_line(fdinfo, size);
	return (free_line(&fdinfo->lines), res);
}

t_line	*fill_lines(t_fd *fdinfo, ssize_t *nsize)
{
	t_line	*curr;
	t_line	*res;

	*nsize = 0;
	res = get_line(fdinfo);
	if (!res)
		return (NULL);
	curr = res;
	while (curr->size && ft_strchr2(curr->buf, '\n') == -1)
	{
		curr->next = get_line(fdinfo);
		if (!curr->next)
		{
			free_line(&res);
			return (NULL);
		}
		*nsize += curr->size;
		curr = curr->next;
	}
	if (ft_strchr2(curr->buf, '\n') != -1)
		curr->size = ft_strchr2(curr->buf, '\n') + 1;
	*nsize += curr->size;
	fill_reste(fdinfo, curr);
	return (res);
}

t_line	*get_line(t_fd *fdinfo)
{
	t_line	*res;
	ssize_t	size;

	res = malloc(sizeof(t_line));
	if (!res)
		return (NULL);
	res->next = NULL;
	size = 0;
	if (fdinfo->reste[size] != '\0')
	{
		while (fdinfo->reste[size] != '\0')
		{
			res->buf[size] = fdinfo->reste[size];
			fdinfo->reste[size++] = '\0';
		}
	}
	else
		size = read(fdinfo->fd, res->buf, BUFFER_SIZE);
	if (size == -1)
		return (free(res), NULL);
	res->buf[size] = '\0';
	res->size = size;
	return (res);
}

char	*make_real_line(t_fd *fdinfo, ssize_t size)
{
	char	*res;
	t_line	*curr;
	ssize_t	i;
	ssize_t	len;

	curr = fdinfo->lines;
	res = malloc(size + 1);
	len = 0;
	if (!res)
		return (NULL);
	while (curr)
	{
		i = -1;
		while (++i < curr->size)
			res[len++] = curr->buf[i];
		curr = curr->next;
	}
	res[len] = '\0';
	return (res);
}

t_ffd	*init_fdinfos(t_ffd *fdinfos)
{
	t_ffd	*new;

	if (!fdinfos)
	{
		new = malloc(sizeof(t_ffd));
		if (!new)
			return (NULL);
		new->first = NULL;
	}
	else
		new = fdinfos;
	return (new);
}
