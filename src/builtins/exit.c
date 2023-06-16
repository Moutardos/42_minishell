/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:56:29 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/16 15:51:01 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	exit_m(t_minishell *mini)
{
	extern int g_exit;
	printf("exit builtlin \n");
	g_exit = 0;
	return (0);
}