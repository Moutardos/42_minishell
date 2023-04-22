/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loic Cozdenmat <Loic Cozdenmat@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:07:04 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/03/09 12:31:26 by Loic Cozden      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		res;
	int		sign;
	size_t	i;

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
