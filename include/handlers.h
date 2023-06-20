/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:57:49 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/20 16:21:27 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

# include "minishell.h"

void	handler(int sig);
void	replace_line(void);
void	setup_signals(void handler(int));
#endif