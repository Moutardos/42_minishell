/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:13:05 by coltcivers        #+#    #+#             */
/*   Updated: 2023/05/29 10:04:14 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_cmd t_cmd;
typedef struct s_minishell t_minishell;


int		quotes(char *line, int index);
int		next_sep_pos(char *str, int pos);
t_cmd	*parse_cmd(int start, int end, char *str);
void	*clear_cmd(t_cmd	*cmd);
t_cmd	*new_cmd(void);
void	free_cmds(t_cmd *cmds);
void	parse_current_cmd(t_minishell *mini);
void	cmd_add_back(t_cmd **cmd, t_cmd *new);



#endif