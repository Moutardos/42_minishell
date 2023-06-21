/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:31:06 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/21 14:43:09 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	assign_delims_offset(char *cmd, char *cmd2, int *data, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (is_delim(cmd, j) && i != 0)
		{
			j++;
			continue ;
		}
		j = get_next_delim(cmd, j);
		data[i] = curr_delim_offset(cmd, j);
		i++;
	}
	data[i] = ft_strlen(cmd2);
}

//echo salut"toi >>> || |" "|" > test."txt" append" append2" ">"
void	get_delims_auxiliary3(t_delims_args *args, \
char *cmd, char *holder)
{
	while (args->i < args->j)
	{
		holder[args->l] = cmd[args->i];
		args->i++;
		args->l++;
	}
	holder[args->l] = '\0';
	args->delim_b++;
}
