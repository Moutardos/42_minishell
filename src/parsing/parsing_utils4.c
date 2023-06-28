/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:06:21 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/28 15:36:26 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static int	next_arg_pos5(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes(str, pos))
		{
			while (!quotes(str, pos) && str[pos] != ' ' && str[pos] != '\0' \
			&& (ft_isalnum(str[pos]) || str[pos] == '_' || str[pos] == '?'))
				pos++;
			return (pos);
		}
		if (quotes(str, pos))
		{
			while (quotes(str, pos) && str[pos] != ' ' && str[pos] != '\0' \
			&& (ft_isalnum(str[pos]) || str[pos] == '_' || str[pos] == '?'))
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
		if (str[i] == '$' && replace_case(str, i))
		{
			j = next_arg_pos5(str, i + 1);
			env = env_from_pos(dico, str, i + 1, j);
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
		return (NULL);
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
