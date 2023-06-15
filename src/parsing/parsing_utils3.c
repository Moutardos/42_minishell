/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:48:51 by hgirard           #+#    #+#             */
/*   Updated: 2023/06/15 19:30:35 by lcozdenm         ###   ########.fr       */
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

int	bltn_args_amount(char *cmd)
{
	int	i;
	int	count;

	i = get_post_bltn(cmd);
	count = 0;
	while (cmd[i] != '\0' && !is_delim(cmd, i))
	{
		if (cmd[i] != ' ')
		{
			i = next_arg_pos(cmd, i);
			count++;
			continue ;
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
	while (i++ < start)
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
	free(str1);
	return (new);
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
