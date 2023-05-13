/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:08:17 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/05 16:40:10 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb > SIZE_MAX / size)
            return (NULL);
	mem = malloc(size * nmemb);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}

