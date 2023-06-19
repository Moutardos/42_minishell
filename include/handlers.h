/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:57:49 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/19 15:35:43 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

# include "minishell.h"

void	handler(int sig, siginfo_t *info, void *c);
void	replace_line(void);
void	setup_signals(void handler(int, siginfo_t, void*));
#endif