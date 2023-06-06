/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:13:05 by coltcivers        #+#    #+#             */
/*   Updated: 2023/05/31 11:29:19 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_cmd t_cmd;
typedef struct s_minishell t_minishell;
typedef enum e_delim t_delim;

int		quotes(char *line, int index);
int		next_sep_pos(char *str, int pos);
t_cmd	*parse_cmd(int start, int end, char *str);
void	*clear_cmd(t_cmd	*cmd);
t_cmd	*new_cmd(void);
void	free_cmds(t_cmd *cmds);
void	parse_current_cmd(t_minishell *mini);
void	cmd_add_back(t_cmd **cmd, t_cmd *new);
int		get_delims_amount(char *str);
int		bltn_args_amount(char *cmd);
int		get_post_bltn(char *str);
int		is_delim(char *cmd, int i);
int		next_arg_pos(char *str, int pos);
void	cmd_del_last(t_cmd *cmd);
void	cmd_del_cmd(t_cmd *cmd);
int		get_next_delim(char *str, int start);
t_delim	get_curr_delim(char *str, int pos);
int		validate_builtin(char *builtin);
char	*str_fullcpy(char *src);

#endif