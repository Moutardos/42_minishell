/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:37:43 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/23 18:01:48 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int	echo(t_cmd *cmd);
int	pwd(t_minishell *mini, int fd);
int	cd(t_minishell *mini, t_cmd *cmd);
int	export_m(t_minishell *mini, t_cmd *cmd);
int	unset(t_minishell *mini, t_cmd *cmd);
int	export_m(t_minishell *mini, t_cmd *cmd);
int	exit_m(t_minishell *mini, t_cmd *cmd);
#endif