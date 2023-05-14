/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:10:29 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/14 17:16:48 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	perror2(char *prefix, char *suffix)
{
	int	total;

	total = 0;
	if (prefix != NULL)
		total += ft_putstr_fd(prefix, 2);
	total += ft_putstr_fd(strerror(errno), 2);
	if (suffix != NULL)
	{
		total += ft_putstr_fd(" ", 2);
		total += ft_putstr_fd(suffix, 2);
	}
	total += ft_putstr_fd("\n", 2);
	return (total);
}