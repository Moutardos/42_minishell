/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:25:34 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/28 13:29:42 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd2(char *s, char *s2, int fd)
{
	size_t	size;
	size_t	size2;

	if (s == NULL)
		return (0);
	size = ft_strlen(s);
	size2 = ft_strlen(s2);
	return (write(fd, s, size) + write(fd, s2, size2) + write(fd, "\n", 1));
}
