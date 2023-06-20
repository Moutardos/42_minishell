/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:09:26 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/20 23:14:46 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumeric(const char *str)
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
