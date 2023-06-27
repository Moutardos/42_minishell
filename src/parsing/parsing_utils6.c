/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:20:11 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/27 17:43:47 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

char	*realloc_quote(char *str)
{
	char		*new;
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

void	parse_current_cmd_utils(t_cmd *cmds)
{
	while (cmds != NULL)
	{
		cmds->fname = cmds->av[0];
		set_builtins(cmds);
		cmds = cmds->next;
	}
}

static int	quotes_test(char *line, int index)
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

//echo "salut toi" "test 'test2'"
//"e""c""h""o" salut
//echo "salut 'test'"
//remove all ',",/ from pos 0 to next delim pos
//echo "$USER ' ' ' '"
char	*expand_bltn(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		value;
	
	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		value = 0;
		//printf("quotes_test(str, i) : %d\n", quotes_test(str, i));
		//printf("i : %d\n", i);
		//printf("char i: %c\n", str[i]);
		//printf("char i+1: %c\n", str[i + 1]);
		if (quotes_test(str, i))
			value = 1;
		if (!quotes_test(str, i + value) && (str[i] == '"' || str[i] == '\'' || str[i] == '\\'))
		{
			//printf("remove \n");
			i++;
			continue ;
		}
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	free(str);
	//printf("new : %s\n", new);
	/*
	if (quotes(new, ft_strlen(new)))
	{
		printf("err post expand \n");
		exit(1);
	}
	*/
	return (new);
}

int	next_arg_pos3(char *str, int pos)
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
			while (quotes(str, pos))
				pos++;
			return (pos + 1);
		}
		pos++;
	}
	return (pos);
}

int	curr_delim_offset(char *str, int pos)
{
	int	i;
	int	offset;

	i = 0;
	offset = 0;
	while (str[i] != '\0' && i <= pos)
	{
		//printf("str[i] : %c\n", str[i]);
		if (((!quotes_test(str, i) || quotes_test(str, i) && !quotes_test(str, i + 1))) \
		&& (str[i] == '"' || str[i] == '\'' || str[i] == '\\'))
		{
		//	printf("reached \n");
			offset++;
		}
		i++;
	}
	//printf("offset : %d\n", offset);
	return (pos - offset);
}
