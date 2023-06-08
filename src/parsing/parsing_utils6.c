/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:20:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/08 12:54:01 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*realloc_quote(char *str)
{
	char	*new;
	int		i;

	new = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	if (!new)
		return (NULL);
	i = 0;
	while (i < ft_strlen(str) - 2)
	{
		new[i] = str[i + 1];
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

void	remove_quotes(t_cmd *cmds)
{
	int	i;
	
	while (cmds != NULL)
	{
		i = 0;
		while (cmds->av[i] != NULL)
		{
			if (cmds->av[i][0] == '\'' \
			|| cmds->av[i][0] == '"')
				cmds->av[i] = realloc_quote(cmds->av[i]);
			i++;
		}
		cmds = cmds->next;
	}
}