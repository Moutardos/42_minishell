/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgirard <hgirard@student.42.f>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:28:01 by hgirard           #+#    #+#             */
/*   Updated: 2023/05/27 22:43:42 by hgirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_fullcpy(char *src)
{
	char	*dst;
	int		i;

	i = 0 ;
	dst = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (NULL);
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i <= index)
	{
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
	return (open);
}

int	next_sep_pos(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes(str, pos) && str[pos] == '|')
			return (pos + 1);
		pos++;
	}
	return (pos);
}

int	validate_builtin(char *builtin)
{
	if (!ft_strncmp(builtin, "echo", 4) || !ft_strncmp(builtin, "cd", 2) || \
	!ft_strncmp(builtin, "pwd", 3) || !ft_strncmp(builtin, "export", 6) || \
	!ft_strncmp(builtin, "unset", 5) || !ft_strncmp(builtin, "env", 3) || \
	!ft_strncmp(builtin, "exit", 4) || !ft_strncmp(builtin, ">>", 2))
		return (1);
	return (0);
}

int	is_sep(char c)
{
	if (c == '"' || c == '\'' || c == ' ' || c == '|' || c == '\0')
		return (1);
	return (0);
}
