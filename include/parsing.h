/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:13:05 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/28 16:58:31 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

int		quotes(char *line, int index);
int		next_sep_pos(char *str, int pos);
t_cmd	*parse_cmd(int start, int end, char *str);
void	*clear_cmd(t_cmd	*cmd);
t_cmd	*new_cmd(void);
void	free_cmds(t_cmd **cmds);
int		parse_current_cmd(t_minishell *mini);
void	cmd_add_back(t_cmd **cmd, t_cmd *new);
int		get_delims_amount(char *str);
int		bltn_args_amount(char *cmd, int end);
int		get_post_bltn(char *str);
int		is_delim(char *cmd, int i);
int		next_arg_pos(char *str, int pos);
void	cmd_del_last(t_cmd *cmd);
void	cmd_del_cmd(t_cmd *cmd);
int		get_next_delim(char *str, int start);
t_delim	get_curr_delim(char *str, int pos);
char	*str_fullcpy(char *src);
char	*get_builtin(char *cmd);
void	get_args(t_cmd *curr_cmd, char *cmd, char *cmd2);
void	get_delims(t_cmd *curr_cmd, t_delims_args *args, char *cmd, char *cmd2);
char	*env_from_pos(t_dico *dico, char *str, int start, int end);
char	*join_from_pos(char *str1, int start, int end, char *env);
int		delims_args_amount(char *cmd);
void	remove_quotes(t_cmd *cmds);
char	*expand_bltn(char *str, int i);
int		curr_delim_offset(char *str, int pos);
char	*realloc_quote(char *str);
int		next_arg_pos3(char *str, int pos);
int		next_arg_pos2(char *str, int pos);
void	assign_delims_offset(char *cmd2, int *data, int size);
void	get_delims_auxiliary3(t_delims_args *args, char *cmd, char *holder);
void	set_builtins(t_cmd *cmd);
int		next_arg_pos4(char *str, int pos);
void	parse_current_cmd_utils(t_cmd *cmds);
int		is_delim2(char *cmd, int i);
int		quotes2(char *line, int index);
int		replace_case(char *str, int pos);
int		next_arg_pos_temp(char *str, int pos);
void	get_args_auxiliary2(t_cmd *curr_cmd, char *cmd2, t_delims_args *a);

#endif