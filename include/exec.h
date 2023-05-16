/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:55:14 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/16 14:37:22 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/wait.h>
# include "minishell.h"
// fork
#define F_ERROR -1
#define F_CHILD 0

// EXEC
int	execute(t_minishell	*mini);

// FILES_UTILS
/* Open each files and store the last fd for in and out inside cmd,
   */
int	redirections(t_cmd *cmd);

/* Try to find if the fname of the command already exist in path, if so
   allocate the path to cmd->path, if not cmd->path is allocated to current
   directory + fname*/
int	check_paths(t_minishell *mini, t_cmd *cmd);

/* Check if file is not stdin or stdout before closing it, return new
*/
int   closef(int fd, int new);


int	here_doc(char *stop, int fd, int is_last);
#endif