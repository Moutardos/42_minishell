/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:06:21 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/07 13:23:10 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_arg_pos2(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes(str, pos))
		{
			while (!quotes(str, pos) && str[pos] != ' ' && str[pos] != '\0' \
			&& !is_delim(str, pos))
				pos++;
			return (pos);
		}
		if (quotes(str, pos))
		{
			while (quotes(str, pos) && str[pos] != ' ' && str[pos] != '$')
				pos++;
			return (pos);
		}
		pos++;
	}
	return (pos);
}

char	*replace_str2(t_dico *dico, char *str)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && quotes(str, i) != 2)
		{
			j = next_arg_pos2(str, i + 1);
			env = env_from_pos(dico, str, i, j);
			str = join_from_pos(str, i, j, env);
			i = j;
			free(env);
			continue ;
		}
		i++;
	}
	return (str);
}

/// @brief Checking builtin / redir validity 
/// @param cmd 
/// @return 
char	*get_builtin(char *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*builtin;

	i = 0;
	while (cmd[i] == ' ' && cmd[i] != '\0')
		i++;
	if (is_delim(cmd, i))
		return (NULL);
	j = i;
	i = next_arg_pos(cmd, i);
	builtin = ft_calloc(i - j + 1, sizeof(char));
	if (!builtin)
		return (0);
	k = 0;
	while (j < i && cmd[j] != ' ')
	{
		builtin[k] = cmd[j];
		k++;
		j++;
	}
	builtin[k] = '\0';
	return (builtin);
}

//return amount, count handled in princip
static int	delims_args_amount_auxiliary(char *cmd, \
int delim_amount, int i, int amount)
{
	while (delim_amount > 0)
	{
		i = get_next_delim(cmd, i);
		if (get_curr_delim(cmd, i) == IN_NL \
		|| get_curr_delim(cmd, i) == OUT_APPEND)
			i ++;
		if (cmd[i] != '\0')
			i++;
		while (cmd[i] != '\0' && !is_delim(cmd, i))
		{
			if (cmd[i] != ' ')
			{
				i = next_arg_pos(cmd, i);
				if (!is_delim(cmd, i))
					amount++;
				continue ;
			}
			i++;
		}
		delim_amount--;
	}
	return (amount);
}

int	delims_args_amount(char *cmd)
{
	int	i;
	int	delim_amount;
	int	amount;

	i = 0;
	amount = 0;
	delim_amount = get_delims_amount(cmd);
	if (delim_amount == 0)
		return (0);
	amount = delims_args_amount_auxiliary(cmd, delim_amount, i, amount);
	return (amount);
}
