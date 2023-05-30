/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:19:34 by hgirard           #+#    #+#             */
/*   Updated: 2023/05/30 18:48:42 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "minishell.h"

//TODO : MODIF CETTE MERDE, AUCUN SENSS I/J
/// @brief Checking builtin / redir validity 
/// @param cmd 
/// @return 
char	*get_builtin(char *cmd)
{
	int		i;
	int		j;
	char	*builtin;
	int		hold;

	j = 0;
	while (cmd[j] == ' ')
		j++;
	i = j;
	while (cmd[i] != ' ')
		i++;
	if (j)
		i--;
	builtin = ft_calloc(i + 1, sizeof(char));
	if (!builtin)
		return (0);
	i = 0;
	while (cmd[j] && i < 6 && cmd[j] != ' ')
	{
		builtin[i] = cmd[j];
		j++;
		i++;
	}
	builtin[i] = '\0';
	return (builtin);
}

int	delims_args_amount(char *cmd)
{
	int		i;
	int		count;
	int		delim_amount;
	int		amount;
	char	*holder;

	count = 0;
	i = 0;
	amount = 0;
	delim_amount = get_delims_amount(cmd);
	if (delim_amount == 0)
		return (0);
	while (count <= delim_amount)
	{
		delims_args_amount_auxiliary(cmd, &i, &amount);
		count++;
	}
	return (amount);
}

int	delims_args_amount_auxiliary(char *cmd, int *in, int *amount)
{
	int	i;

	i = *in;
	i = get_next_delim(cmd, i);
	if ((get_curr_delim(cmd, i) == IN_NL \
	|| get_curr_delim(cmd, i)) == OUT_APPEND)
		i++;
	i++;
	while (cmd[i] != '\0' && cmd[i] != '>' && cmd[i] != '<')
	{
		if (cmd[i] != ' ')
		{
			i = next_arg_pos(cmd, i);
			*amount++;
			continue ;
		}
		i++;
	}
}

/// @brief Get the builtin args, before any next redirection
/// @param curr_cmd 
/// @param cmd 
/// @return 
int	get_args(t_cmd *curr_cmd, char *cmd, char *builtin)
{
	int	j;
	int	l;

	j = 0;
	curr_cmd->ac = 1;
	curr_cmd->av = ft_calloc(bltn_args_amount(cmd) \
	+ delims_args_amount(cmd) + 2, sizeof(char *));
	if (!curr_cmd->av)
		return (1);
	curr_cmd->av[0] = builtin;
	get_args_auxiliary(curr_cmd, cmd, 0, 0);
	return (1);
}

int	get_args_auxiliary(t_cmd *curr_cmd, char *cmd, int l, int j)
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
				return (1);
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

/// @brief Get the cmd delims redirection, and associated files
/// @param cmd 
/// @return 
int	get_delims(t_cmd *curr_cmd, char *cmd)
{
	int		i;
	int		j;
	int		count;
	int		m;
	int		n;
	int		l;
	int		delim_b;
	char	*holder;

	count = 0;
	i = 0;
	m = 0;
	n = 0;
	if ((curr_cmd->delim_amount = get_delims_amount(cmd)) == 0)
		return (-1);
	curr_cmd->delim = ft_calloc((curr_cmd->delim_amount + 1), sizeof(t_delim));
	if (!curr_cmd->delim)
		return (1);
	//TODO : MODIF ARG AMOUNT
	curr_cmd->delim_f = ft_calloc(1000 ,sizeof(char *));
	while (count < curr_cmd->delim_amount)
	{
		delim_b = 0;
		i = get_next_delim(cmd, i);
		if ((curr_cmd->delim[count] = get_curr_delim(cmd, i)) == IN_NL \
		|| (curr_cmd->delim[count] = get_curr_delim(cmd, i)) == OUT_APPEND)
			i ++;
		//printf("Delim : %d\n", curr_cmd->delim[count]);
		i++;
		while (cmd[i] != '\0' && cmd[i] != '>' && cmd[i] != '<')
		{
			/*
			holder = curr_cmd->delim_f[m];
			if (!delim_b)
				holder = curr_cmd->av[curr_cmd->ac + m];
			*/
			if (cmd[i] != ' ')
			{
				l = 0;
				j = next_arg_pos(cmd, i);
				//printf("curr delim : %d\n", i);
				//printf("next_arg_pos : %d\n", j);
				///holder = ft_calloc(j - i + 1, sizeof(char));
				if (delim_b == 0)
				{
					curr_cmd->delim_f[n] = ft_calloc(j - i + 1, sizeof(char));
					holder = curr_cmd->delim_f[n];
					n++;
				}
				else
				{
					//printf("curr_cmd->av + m %d\n", curr_cmd->ac + m);
					curr_cmd->av[curr_cmd->ac + m] = ft_calloc(j - i + 1, sizeof(char));
					holder = curr_cmd->av[curr_cmd->ac + m];
					m++;
				}
				while (i < j)
				{
					holder[l] = cmd[i];
					i++;
					l++;
				}
				holder[l] = '\0';
				delim_b++;
				//printf("curr_cmd->av[curr_cmd->ac + m]: %s\n", curr_cmd->av[curr_cmd->ac + m]);
				//printf("curr_cmd->av[curr_cmd->ac -1]: %s\n", curr_cmd->av[curr_cmd->ac - 1]);
				//free(holder);
				continue;
			}
			i++;
			j++;
		}
		count++;
	}
	curr_cmd->av[curr_cmd->ac + m] = NULL;
	curr_cmd->delim_f[n] = NULL;
	return (0);
}

t_cmd	*parse_cmd(int start, int end, char *str)
{
	int		j;
	char	*temp;
	char	*copy;
	char	*copy2;
	char	**args;
	char	*builtin;
	t_cmd   *cmd;
	int i;

	j = 0;
	temp = ft_calloc(end - start + 1, sizeof(char));
	while (start < end)
	{
		temp[j] = str[start];
		start++;
		j++;
	}
	temp[j] = '\0';
	builtin = get_builtin(temp);
	if (!validate_builtin(builtin))
		printf("Unsuported builtin provided, still going on\n");
	cmd = new_cmd();
	printf("=============\n");
	printf("Builtin args : \n");
	copy = str_fullcpy(temp);
	copy2 = str_fullcpy(temp);
	get_args(cmd, copy, builtin);
	get_delims(cmd, copy2);
	i = 0;
	while (cmd->av[i] != NULL)
	{
		printf("arg : %s\n", cmd->av[i]);
		i++;
	}
	printf("/////////////\n");
	printf("Builtin redirections : \n");
	i = 0;
	while (i < cmd->delim_amount)
	{
		printf("delim : %d\n", cmd->delim[i]);
		printf("delim_f : %s\n", cmd->delim_f[i]);
		i++;
	}
	cmd->in = STDIN;
	cmd->out = STDOUT;
	free(temp);
	free(copy);
	free(copy2);
	return (cmd);
}

/*
int main (void) {

	char test1[] = "cat client_bonus.c | wc -l 'test |'";
	char test2[] = "echo \"salut toi |\" > test.txt append > \"test2.txt\"append << test3.txt";
	char test3[] = "cd test.txt";
	char test4[] = "echo \"salut toi | \"";
	char test5[] = "echo \"bonjour\" | >> a";
	char test6[] = "echo \"bonjour\" | cd rewrwerwe | echo rewrwerew \" | \" ";
	char test7[] = "echo \"bonjour\" | echot rewrwerwe | echo rewrwerew \" | \" ";
	char test8[] = "echo    \"bonjour\"'fdsfrtryt' rewrwerew \" | \" < test.txt >> test2.txt";
	char test9[] = "echo  ee\"   bonjour test\"ee'tete'rewrwqe \"|\"    fdsfrtryt rewrwerew \" | \" ";
	char test10[] = "echo \"salut |\" > test.txt append append ete\"etere\"> \"test2.txt\"append\"e\" << test3.txt\"etere\"";

	//assign_cmds(test1);
	printf("/////////////////\n");
	parser(test2);
	printf("/////////////////\n");
	parser(test3);
	printf("/////////////////\n");
	parser(test4);
	printf("/////////////////\n");
	parser(test5);
	printf("/////////////////\n");
	parser(test6);
	printf("/////////////////\n");
	parser(test7);
	printf("/////////////////\n");
	parser(test8);
	printf("/////////////////\n");
	parser(test9);
	printf("/////////////////\n");
	parser(test10);
	printf("/////////////////\n");
}
*/