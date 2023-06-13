/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:13:05 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/13 19:18:22 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_cmd t_cmd;
typedef struct s_minishell t_minishell;
typedef enum e_delim t_delim;
typedef struct s_delims_args t_delims_args;

int		quotes(char *line, int index);
int		next_sep_pos(char *str, int pos);
t_cmd	*parse_cmd(int start, int end, char *str);
void	*clear_cmd(t_cmd	*cmd);
t_cmd	*new_cmd(void);
void	free_cmds(t_cmd **cmds);
int		parse_current_cmd(t_minishell *mini);
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
char	*get_builtin(char *cmd);
void	get_args(t_cmd *curr_cmd, char *cmd, char *builtin);
int		get_delims(t_cmd *curr_cmd, t_delims_args *args, char *cmd);
char	*env_from_pos(t_dico *dico, char *str, int start, int end);
char	*join_from_pos(char *str1, int start, int end, char *env);
int		delims_args_amount(char *cmd);
void	remove_quotes(t_cmd *cmds);


#endif