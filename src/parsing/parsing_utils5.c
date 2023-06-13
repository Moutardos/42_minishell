/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:33:21 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/13 21:48:50 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static void	get_args_auxiliary(t_cmd *curr_cmd, char *cmd, int l, int j)
{
	int	i;

	i = get_post_bltn(cmd);
	while (cmd[i] != '\0' && !is_delim(cmd, i))
	{
		if (cmd[i] != ' ')
		{
			l = 0;
			j = next_arg_pos(cmd, i);
			curr_cmd->av[curr_cmd->ac] = ft_calloc(j - i + 1, sizeof(char));
			if (!curr_cmd->av[curr_cmd->ac])
				return ;
			while (i < j)
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
void	get_args(t_cmd *curr_cmd, char *cmd, char *builtin)
{
	int	alloc;
	int	test;

	alloc = bltn_args_amount(cmd) \
	+ delims_args_amount(cmd);
	//printf("bltn_args_amount(cmd) : %d\n", bltn_args_amount(cmd));
	//printf("delims_args_amount(cmd) : %d\n", delims_args_amount(cmd));
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
	get_args_auxiliary(curr_cmd, cmd, 0, 0);
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
	args->delim_b++;
}

static void	get_delims_auxiliary(t_cmd *c, t_delims_args *a, char *cmd, \
char *holder)
{
	while (cmd[a->i] != '\0' && !is_delim(cmd, a->i))
	{
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
int	get_delims(t_cmd *curr_cmd, t_delims_args *args, char *cmd)
{
	char			*holder;

	holder = NULL;
	curr_cmd->delim_amount = get_delims_amount(cmd);
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
		args->i = get_next_delim(cmd, args->i);
		curr_cmd->delim[args->count] = get_curr_delim(cmd, args->i);
		if (curr_cmd->delim[args->count] == IN_NL \
		|| curr_cmd->delim[args->count] == OUT_APPEND)
			args->i ++;
		args->i++;
		get_delims_auxiliary(curr_cmd, args, cmd, holder);
		args->count++;
	}
	curr_cmd->av[curr_cmd->ac + args->m] = NULL;
	curr_cmd->delim_f[args->n] = NULL;
	return (free(args), 0);
}
