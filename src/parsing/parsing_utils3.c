/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:48:51 by hgirard           #+#    #+#             */
/*   Updated: 2023/06/28 17:05:55 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_delim	get_curr_delim(char *str, int pos)
{
	if (str[pos] == '>')
	{
		if (str[pos + 1] == '>')
			return (OUT_APPEND);
		return (OUT);
	}
	else if (str[pos] == '<')
	{
		if (str[pos + 1] == '<')
			return (IN_NL);
		return (IN);
	}
	return (NONE);
}

int	bltn_args_amount(char *cmd, int end)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i] != '\0' && i < end)
	{
		if (quotes(cmd, i))
		{
			count++;
			i = next_arg_pos3(cmd, i);
		}
		else if (cmd[i] != ' ')
		{
			i = next_arg_pos3(cmd, i);
			count++;
		}
		i++;
	}
	return (count);
}

void	*clear_cmd(t_cmd	*cmd)
{
	while (cmd && cmd->next != NULL)
		cmd_del_last(cmd);
	cmd_del_cmd(cmd);
	return (NULL);
}

char	*join_from_pos(char *str1, int start, int end, char *env)
{
	char	*new;
	int		i;

	i = -1;
	new = ft_calloc(ft_strlen(str1) \
	+ ft_strlen(env) + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (i++ < start && str1[i] != '$')
		new[i] = str1[i];
	i = 0;
	while (env[i] != '\0')
	{
		new[start] = env[i];
		i++;
		start++;
	}
	while (str1[end] != '\0')
	{
		new[start] = str1[end];
		end++;
		start++;
	}
	new[start] = '\0';
	return (free(str1), new);
}

char	*env_from_pos(t_dico *dico, char *str, int start, int end)
{
	char	*new;
	int		i;
	char	*rep;

	i = 0;
	new = ft_calloc(end - start + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (start < end)
	{
		new[i] = str[start];
		start++;
		i++;
	}
	new[i] = '\0';
	rep = get_dico(dico, new);
	free(new);
	return (rep);
}
