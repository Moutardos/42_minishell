/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:13:05 by coltcivers        #+#    #+#             */
/*   Updated: 2023/05/06 00:11:00 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

void	parse_current_cmd(t_minishell *mini);
int		quote_check(char *line, int index);
int		quotes(char *line, int index);
int		is_sep(char c);
int		next_sep_pos(char *str, int pos);

t_cmd	*new_cmd(char *delim);
t_cmd	*cmd_last(t_cmd *lst);
t_cmd	*cmd_first(t_cmd *lst);
void	cmd_add_back(t_cmd **cmd, t_cmd *new);
void	cmd_del_last(t_cmd **cmd);

#endif