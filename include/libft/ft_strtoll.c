/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loic Cozdenmat <Loic Cozdenmat@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:30:37 by Loic Cozden       #+#    #+#             */
/*   Updated: 2023/03/09 12:39:19 by Loic Cozden      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_strtoll(const char *nptr)
{
	long long	res;
	int			sign;
	size_t		i;

	res = 0;
	i = 0;
	sign = 1;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		res *= 10;
		res += (nptr[i] - '0') * sign;
		i++;
	}
	return (res);
}
