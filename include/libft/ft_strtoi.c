/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loic Cozdenmat <Loic Cozdenmat@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:43 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/03/09 12:31:57 by Loic Cozden      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_numeric(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && (i != 0 && str[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}

int	*ft_strtoi(const char *str, int *size)
{
	char			**tatoi;
	int				*res;
	unsigned int	len;
	unsigned int	i;

	tatoi = ft_split(str, ' ');
	if (!tatoi)
		return (NULL);
	len = -1;
	while (tatoi[++len])
		if (!ft_is_numeric(tatoi[len]))
			return (ft_free_split(tatoi), NULL);
	res = malloc(sizeof(int) * len);
	i = -1;
	while (res && ++i < len)
	{
		if (ft_strtoll(tatoi[i]) > INT_MAX || ft_strtoll(tatoi[i]) < INT_MIN)
			return (ft_free_split(tatoi), free(res), NULL);
		res[i] = ft_atoi(tatoi[i]);
	}
	*size = len;
	return (ft_free_split(tatoi), res);
}
