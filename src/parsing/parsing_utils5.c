/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:21 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/17 20:52:57 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

//echo "salut""toi < test" > test".txt""append""colle" > test2
//prends pos du delim actuel, lui soustrait l'offset le precedant
int curr_delim_offset(char *str, int pos)
{
	int i;
	int offset;

	i = 0;
	offset = 0;
	while (str[i] != '\0' && i < pos)
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '\\')
			offset++;
		i++;
	}
	//printf("offset : %d\n", offset);
	return (pos - offset);
}

static void assign_delims_offest(char *cmd, char *cmd2, int *data, int size)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (is_delim(cmd, j))
		{
			j++;
			continue ;
		}
		j = get_next_delim(cmd, j);
		//printf("j : %d\n", j);
		data[i] = curr_delim_offset(cmd, j);
		//printf("curr_delim_offset : %d\n", data[i]);
		i++;
	}
	//printf("last i allocated: %d\n", i);
	data[i] = ft_strlen(cmd2) + 1;
	//printf("data[i] %d\n", data[i]);
}


static int	next_arg_pos2(char *str, int pos)
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

// echo salut"toi << test"t
static void	get_args_auxiliary(t_cmd *curr_cmd, char *cmd, int l, int j, int delim_offset)
{
	int	i;

	i = get_post_bltn(cmd);
	//ICI RECUP OFFSET
	//printf("post bltn : %d\n", i);
	//printf("for string : %s\n", cmd);
	while (cmd[i] != '\0' && i < delim_offset)
	{
		//if (cmd[i] != ' ' && !is_delim(cmd, i))
		if (cmd[i] != ' ')
		{
			l = 0;
			j = next_arg_pos2(cmd, i);
			if (is_delim(cmd, j));
				j++;
			//printf("cmd[i] : %c\n", cmd[i]);
			//printf("cmd[i+1] : %c\n", cmd[i + 1]);
			//printf("curr_cmd->ac : %d\n", curr_cmd->ac);
			curr_cmd->av[curr_cmd->ac] = ft_calloc(j - i + 1, sizeof(char));
			if (!curr_cmd->av[curr_cmd->ac])
				return ;
			while (i < j - 1)
			{
				curr_cmd->av[curr_cmd->ac][l] = cmd[i];
				i++;
				l++;
			}
			curr_cmd->av[curr_cmd->ac][l] = '\0';
			curr_cmd->ac++;
			continue ;
		}
		i++;
		j++;
	}
}

/// @brief Get the builtin args, before any next redirection
/// @param curr_cmd 
/// @param cmd 
/// @return 
void	get_args(t_cmd *curr_cmd, char *cmd, char *cmd2, char *builtin)
{
	int	alloc;
	int	test;
	int	delim_offset;

	alloc = bltn_args_amount(cmd2) \
	+ delims_args_amount(cmd2);
	//printf("bltn_args_amount(cmd2) : %d\n", bltn_args_amount(cmd2));
	//printf("bltn_args_amount(cmd) : %d\n", bltn_args_amount(cmd));
	//printf("delims_args_amount(cmd) : %d\n", delims_args_amount(cmd2));
	//printf("alloc : %d\n", alloc);
	curr_cmd->ac = 1;
	curr_cmd->av = ft_calloc(alloc + 2, sizeof(char *));
	if (!curr_cmd->av)
		return ;
	if (builtin != NULL)
		curr_cmd->av[0] = builtin;
	test = 0;
	while (cmd[test] == ' ')
		test++;
	if (is_delim(cmd, test))
		return ;
	delim_offset = curr_delim_offset(cmd2, get_next_delim(cmd2, 0));
	//printf("delim_offset : %d\n", delim_offset);
	get_args_auxiliary(curr_cmd, cmd, 0, 0, delim_offset);
	return ;
}

static void	get_delims_auxiliary2(t_delims_args *args, \
char *cmd, char *holder)
{
	while (args->i < args->j)
	{
		holder[args->l] = cmd[args->i];
		args->i++;
		args->l++;
	}
	holder[args->l] = '\0';
	//printf("holder : %s\n", holder);
	args->delim_b++;
}

//echo salut > test | echo test
static void	get_delims_auxiliary(t_cmd *c, t_delims_args *a, char *cmd, \
char *holder, int delim_offset_index)
{
	//METTRE ICI && A->I < c[]
	//printf("delim_offset_index : %d\n", delim_offset_index);
	//printf("delim_offset_index + 1 : %d\n", delim_offset_index + 1);
	//printf("delim_offset_index : %d\n", delim_offset_index);
	//printf("cmd : %s\n", cmd);
	//printf("c->offset_delims[delim_offset_index + 1] : %d\n", c->offset_delims[delim_offset_index + 1]);
	while (cmd[a->i] != '\0' && cmd[a->i] != '|' && a->i < c->offset_delims[delim_offset_index + 1])
	{
		//printf("i : %d\n", a->i);
		//printf("cmd[i] : %c\n", cmd[a->i]);
		//printf("cmd[i + 1] : %c\n", cmd[a->i + 1]);
		if (cmd[a->i] != ' ')
		{
			a->l = 0;
			a->j = next_arg_pos(cmd, a->i);
			if (a->delim_b == 0)
			{
				c->delim_f[a->n] = ft_calloc(a->j - a->i + 1, 1);
				holder = c->delim_f[a->n];
				a->n++;
			}
			else
			{
				c->av[c->ac + a->m] = ft_calloc(a->j - a->i + 1, 1);
				holder = c->av[c->ac + a->m];
				a->m++;
			}
			get_delims_auxiliary2(a, cmd, holder);
			continue ;
		}
		a->i++;
		a->j++;
	}
}

/// @brief Get the cmd delims redirection, and associated files
/// @param cmd 
/// @return 
int	get_delims(t_cmd *curr_cmd, t_delims_args *args, char *cmd, char *cmd2)
{
	char			*holder;

	holder = NULL;
	curr_cmd->delim_amount = get_delims_amount(cmd);
	//printf("curr_cmd->delim_amount : %d\n", curr_cmd->delim_amount);
	curr_cmd->offset_delims = ft_calloc(sizeof(int), curr_cmd->delim_amount + 1);
	assign_delims_offest(cmd2, cmd, curr_cmd->offset_delims, curr_cmd->delim_amount);
	if (curr_cmd->delim_amount == 0)
	{
		curr_cmd->delim = NULL;
		curr_cmd->delim_f = ft_calloc(curr_cmd->delim_amount + 1, sizeof(char *));
		if (!curr_cmd->delim_f)
			return (free(args), 1);
		curr_cmd->delim_f[0] = NULL;
		return (free(args), 0);
	}
	curr_cmd->delim = ft_calloc((curr_cmd->delim_amount + 1), sizeof(t_delim));
	if (!curr_cmd->delim)
		return (free(args), 1);
	curr_cmd->delim_f = ft_calloc(curr_cmd->delim_amount + 1, sizeof(char *));
	if (!curr_cmd->delim_f)
		return (free(args), 1);
	while (args->count < curr_cmd->delim_amount)
	{
		args->delim_b = 0;
		//args->i = get_next_delim(cmd, args->i);
		args->i = curr_cmd->offset_delims[args->count];
		//printf("args->i : %d\n", args->i);
		//printf("cmd[args->i] : %c\n", cmd[args->i]);
		curr_cmd->delim[args->count] = get_curr_delim(cmd, args->i);
		//printf("curr_cmd->delim[args->count] : %d\n", curr_cmd->delim[args->count]);
		if (curr_cmd->delim[args->count] == IN_NL \
		|| curr_cmd->delim[args->count] == OUT_APPEND)
			args->i ++;
		args->i++;
		get_delims_auxiliary(curr_cmd, args, cmd, holder, args->count);
		args->count++;
	}
	curr_cmd->av[curr_cmd->ac + args->m] = NULL;
	curr_cmd->delim_f[args->n] = NULL;
	return (free(args), 0);
}

//echo "salut""toi < test" > test".txt""append""colle" > test2
//echo saluttoi < test > test.txtappendcolle > test2
