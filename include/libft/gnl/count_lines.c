/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:49:24 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/02/09 09:00:16 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	count_lines(int fd)
{
	int		total;
	char	*line;

	total = 0;
	line = get_next_line(fd);
	while (line)
	{
		total++;
		free(line);
		line = get_next_line(fd);
	}
	return (total);
}
