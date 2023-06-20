/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:43 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/20 23:14:54 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		if (!ft_isnumeric(tatoi[len]))
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
