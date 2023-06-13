/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:37:43 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/06/13 19:32:40 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_cmd *cmd);
int	pwd(t_minishell *mini, int fd);
int	cd(t_minishell *mini);
int export(t_minishell *mini, t_cmd *cmd);