/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:20:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/16 20:15:31 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static char	*realloc_quote(char *str)
{
	char	*new;
	size_t		i;

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

static int	quotes_amount(char *str)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '\\')
			count++;
		i++;
	}
	return (count);
}

//remove all ',",/ from pos 0 to next delim pos 
char 	*expand_bltn(char *str)
{
	char	*new;
	int		i;
	int		j;
	
	//printf("next delim : %d\n", next_delim);
	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	//printf("alloced: %d\n", next_delim - quotes_amount(str, next_delim) \
	+ 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '\\')
		{
			i++;
			continue ;
		}
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	free(str);
	return new;
}