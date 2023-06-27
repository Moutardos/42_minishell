/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:21 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/27 21:48:48 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"


int	next_arg_pos4(char *str, int pos)
{
	while (str[pos] != ' ' && str[pos] != '\0')
		pos++;
	return (pos);
}

static int	quotes_temp(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i < index)
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

/*
static int	next_arg_pos_temp(char *str, int pos)
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
			while (quotes(str, pos))
				pos++;
			return (pos);
		}
		pos++;
	}
	return (pos);
}
*/

static int	next_arg_pos_temp(char *str, int pos)
{
	while (str[pos] != '\0')
	{
		if (!quotes_temp(str, pos) && str[pos] == ' ')
			return (pos);
		pos++;
	}
	if (pos > 0 && (str[pos - 1] == '\'' || str[pos - 1] == '"'))
		return (pos - 1);
	return (pos);
}

//echo coltcivers '
//echo "salut 'test' ee' "
static void	get_args_auxiliary(t_cmd *curr_cmd, char *cmd, char *cmd2, 
t_delims_args *a, int delim_offset)
{
	a->i = get_post_bltn(cmd);
	//printf("for cmd : %s\n", cmd);
	//printf("for cmd2 : %s\n", cmd2);
	//printf("delim_offset : %d\n", delim_offset);
	//echo coltcivers '" > test
	a->i = 0;
	while (cmd2[a->i] != '\0' && !is_delim(cmd2, a->i))
	{
		//printf("i %d\n", a->i);
		//printf("a->i <= delim_offset %d\n", a->i <= delim_offset);
		//if (((!quotes_test(str, i) || quotes_test(str, i) && !quotes_test(str, i + 1)))
		if ((cmd2[a->i] == ' ' || cmd2[a->i] == '\'' || cmd2[a->i] == '"')\
		&& (!quotes_temp(cmd2, a->i) || (quotes_temp(cmd2, a->i) \
		&& !quotes_temp(cmd2, a->i + 1))))
		{
			a->i++;
			a->j++;
			continue ;
		}
			a->l = 0;
			//CE SERA A MODIFIER POUR CORRESPONDRE AUX ESPACES COMME ARG
			a->j = next_arg_pos_temp(cmd2, a->i);
			printf("next arg pos %d\n", a->j);
			curr_cmd->av[curr_cmd->ac] = ft_calloc(a->j - a->i + 1, \
			sizeof(char));
			if (!curr_cmd->av[curr_cmd->ac])
				return ;
			while (a->i < a->j)
			{
				if ((cmd2[a->i] == '\'' || cmd2[a->i] == '"')\
				&& (!quotes_temp(cmd2, a->i) || (quotes_temp(cmd2, a->i) \
				&& !quotes_temp(cmd2, a->i + 1))))
				{
					a->i++;
					continue ;
				}
				curr_cmd->av[curr_cmd->ac][a->l] = cmd2[a->i];
				a->i++;
				a->l++;
			}
			curr_cmd->av[curr_cmd->ac][a->l] = '\0';
			printf("arg : %s\n", curr_cmd->av[curr_cmd->ac]);
			curr_cmd->ac++;
			//continue ;
	}
	//printf("out of loop \n");
	free(a);
}

//echo "$USER ' ' ' | " > test
//echo coltcivers ' ' ' |  > test

// echo salut"toi >>> || |" "|" > test."txt" append" append2" ">"
/// @brief Get the builtin args, before any next redirection
/// @param curr_cmd 
/// @param cmd 
/// @return 
void	get_args(t_cmd *curr_cmd, char *cmd, char *cmd2, char *builtin)
{
	int	alloc;
	int	test;
	int	delim_offset;

	//printf("get_next_delim(cmd2, 0) : %d\n", get_next_delim(cmd2, 0));
	delim_offset = curr_delim_offset(cmd2, get_next_delim(cmd2, 0));
	//delim_offset =  get_next_delim(cmd, 0);
	alloc = bltn_args_amount(cmd, delim_offset) \
	+ delims_args_amount(cmd2);
	//printf("delim_offset : %d\n", delim_offset);
	//printf("get_args cmd : %s\n", cmd);
	//printf("get_args cmd2 : %s\n", cmd2);
	//printf("bltn_args_amount(cmd, delim_offset) : %d\n", bltn_args_amount(cmd, delim_offset));
	//printf("delims_args_amount(cmd2) : %d\n", delims_args_amount(cmd2));
	curr_cmd->av = ft_calloc(alloc + 2, sizeof(char *));
	if (!curr_cmd->av)
		return ;
	//if (builtin != NULL && ft_strcmp(builtin, ""))
	//{
	//	curr_cmd->av[0] = builtin;
	//	curr_cmd->ac = 1;
	//}
	test = 0;
	while (cmd[test] == ' ')
		test++;
	if (is_delim(cmd, test))
		return ;
	get_args_auxiliary(curr_cmd, cmd, cmd2, ft_calloc(sizeof(t_delims_args), 1), \
	delim_offset);
	return ;
}

//echo salut toi " ||||| || | || " > test".txt" append2">" "|||"
static void	get_delims_auxiliary2(t_cmd *c, t_delims_args *a, char *cmd, \
int delim_offset_index)
{
	while (a->i < c->offset_delims[delim_offset_index + 1] && \
	cmd[a->i] != '\0')
	//cmd[a->i] != '\0' && cmd[a->i] != '|')
	{
		//printf("a->i : %d\n", a->i);
		//printf("c->offset_delims[delim_offset_index + 1]: %d\n", \
		c->offset_delims[delim_offset_index + 1]);
		//printf("cmd[a->i] : %c\n", cmd[a->i]);
		if (cmd[a->i] != ' ')
		{
			a->l = 0;
			a->j = next_arg_pos4(cmd, a->i);
			if (a->delim_b == 0)
			{
				c->delim_f[a->n] = ft_calloc(a->j - a->i + 1, 1);
				a->holder = c->delim_f[a->n];
				a->n++;
			}
			else
			{
				c->av[c->ac + a->m] = ft_calloc(a->j - a->i + 1, 1);
				a->holder = c->av[c->ac + a->m];
				a->m++;
			}
			get_delims_auxiliary3(a, cmd, a->holder);
			continue ;
		}
		a->i++;
		a->j++;
	}
}

static int	get_delims_auxiliary1(t_cmd *curr_cmd, t_delims_args *args, \
char *cmd, char *cmd2)
{
	curr_cmd->delim_a = get_delims_amount(cmd2);
	curr_cmd->offset_delims = ft_calloc(sizeof(int), curr_cmd->delim_a + 1);
	assign_delims_offset(cmd2, cmd, curr_cmd->offset_delims, curr_cmd->delim_a);
	if (curr_cmd->delim_a == 0)
	{
		curr_cmd->delim = NULL;
		curr_cmd->delim_f = ft_calloc(curr_cmd->delim_a + 1, sizeof(char *));
		if (!curr_cmd->delim_f)
			return (free(args), 1);
		curr_cmd->delim_f[0] = NULL;
		return (free(args), 1);
	}
	return (0);
}

/// @brief Get the cmd delims redirection, and associated files
/// @param cmd 
/// @return 
void	get_delims(t_cmd *curr_cmd, t_delims_args *args, char *cmd, char *cmd2)
{
	if (get_delims_auxiliary1(curr_cmd, args, cmd, cmd2))
		return ;
	curr_cmd->delim = ft_calloc((curr_cmd->delim_a + 1), sizeof(t_delim));
	if (!curr_cmd->delim)
		return (free(args));
	curr_cmd->delim_f = ft_calloc(curr_cmd->delim_a + 1, sizeof(char *));
	if (!curr_cmd->delim_f)
		return (free(args));
	while (args->count < curr_cmd->delim_a)
	{
		args->delim_b = 0;
		args->i = curr_cmd->offset_delims[args->count];
		//printf("args->i : %d\n", args->i);
		//printf("cmd : %s\n", cmd);
		//printf("cmd[i] : %c\n", cmd[args->i]);
		curr_cmd->delim[args->count] = get_curr_delim(cmd, args->i);
		if (curr_cmd->delim[args->count] == IN_NL \
		|| curr_cmd->delim[args->count] == OUT_APPEND)
			args->i ++;
		args->i++;
		get_delims_auxiliary2(curr_cmd, args, cmd, args->count);
		args->count++;
	}
	curr_cmd->av[curr_cmd->ac + args->m] = NULL;
	curr_cmd->delim_f[args->n] = NULL;
	return (free(args));
}
