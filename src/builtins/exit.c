/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:56:29 by coltcivers        #+#    #+#             */
/*   Updated: 2023/06/13 21:25:04 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	exit_m(t_minishell *mini)
{
	printf("exit builtlin \n");
	mini->exit = 0;
	return (0);
}