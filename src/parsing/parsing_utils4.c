/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:06:21 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/27 14:49:02 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	next_arg_pos2(char *str, int pos)
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

static int	quotes_test2(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	//if (index == ft_strlen(line) - 1)
	//	index++;
	while (line[i] && i < index)
	{
		//printf("open : %d\n", open);
		//printf("line[i] : %c\n", line[i]);
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	//printf("return openc: %d\n", open);
	return (open);
}
//if ((!quotes_test2(str, i) || (quotes_test2(str, i) && !quotes_test(str, i + 1))
//check wether replace or not depending on earliest valid quotes found
static int replace_case(char *str, int pos)
{
	int	i;

	i = pos;
	//printf("pos : %d\n", pos);
	while (i > 0 && quotes_test2(str, i))
		i--;
	//printf("i : %d\n", i);
	//printf("str[i] : %c\n", str[i]);
	//printf("str[i + 1] : %c\n", str[i + 1]);
	if (str[i] == '\'')
		return (0);
	return (1);
}

static int	next_arg_pos5(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes(str, pos))
		{
			while (!quotes(str, pos) && str[pos] != ' ' && str[pos] != '\0')
				pos++;
			return (pos);
		}
		if (quotes(str, pos))
		{
			while (quotes(str, pos) && str[pos] != ' ' && str[pos] != '\0')
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
	//printf("str replace_str2: %s\n", str);
	while (str[i] != '\0')
	{
		if (str[i] == '$' && replace_case(str, i))
		{
			//printf("replace case : %d\n", replace_case(str, i));
			//j = next_arg_pos4(str, i + 1);
			j = next_arg_pos5(str, i + 1);
			//i == debut de la var env, j fin
			env = env_from_pos(dico, str, i + 1, j);
			str = join_from_pos(str, i, j, env);
			i = j;
			free(env);
			continue ;
		}
		i++;
	}
	//printf("str post replace_str2: %s\n", str);
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
