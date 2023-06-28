/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:21 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/28 17:13:11 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static void	get_args_auxiliary(t_cmd *curr_cmd, char *cmd2,
t_delims_args *a)
{
	a->i = 0;
	while (cmd2[a->i] != '\0' && !is_delim(cmd2, a->i))
	{
		if ((cmd2[a->i] == ' ' || cmd2[a->i] == '\'' || cmd2[a->i] == '"') \
		&& (!quotes2(cmd2, a->i) || (quotes2(cmd2, a->i) \
		&& !quotes2(cmd2, a->i + 1))))
		{
			a->i++;
			a->j++;
			continue ;
		}
		a->l = 0;
		a->j = next_arg_pos_temp(cmd2, a->i);
		if (cmd2[a->j - 1] == '>' || cmd2[a->j - 1] == '<' || \
		cmd2[a->j - 1] == '|' || cmd2[a->j - 1] == '\'' \
		|| cmd2[a->j - 1] == '"')
			a->j--;
		get_args_auxiliary2(curr_cmd, cmd2, a);
	}
	free(a);
}

// echo salut"toi >>> || |" "|" > test."txt" append" append2" ">"
/// @brief Get the builtin args, before any next redirection
/// @param curr_cmd 
/// @param cmd 
/// @return 
void	get_args(t_cmd *curr_cmd, char *cmd, char *cmd2)
{
	int	alloc;
	int	test;
	int	delim_offset;

	delim_offset = curr_delim_offset(cmd2, get_next_delim(cmd2, 0));
	alloc = ft_strlen(cmd2) \
	+ delims_args_amount(cmd2);
	curr_cmd->av = ft_calloc(alloc + 4, sizeof(char *));
	if (!curr_cmd->av)
		return ;
	test = 0;
	while (cmd2[test] == ' ')
		test++;
	if (is_delim(cmd, test))
		return ;
	get_args_auxiliary(curr_cmd, cmd2, \
	ft_calloc(sizeof(t_delims_args), 1));
	return ;
}

static void	get_delims_auxiliary2(t_cmd *c, t_delims_args *a, char *cmd, \
int delim_offset_index)
{
	while (a->i < c->offset_delims[delim_offset_index + 1] && \
	cmd[a->i] != '\0')
	{
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
char *cmd2)
{
	curr_cmd->delim_a = get_delims_amount(cmd2);
	curr_cmd->offset_delims = ft_calloc(sizeof(int), curr_cmd->delim_a + 1);
	assign_delims_offset(cmd2, curr_cmd->offset_delims, curr_cmd->delim_a);
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
	if (get_delims_auxiliary1(curr_cmd, args, cmd2))
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
