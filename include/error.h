/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:33:17 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/01 12:55:26 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// GOOD : we good
// ERR_ALLOC : malloc failed
// ERR_CMD_NOARG : no argument 
// ERR_CMD_DUPX   : dup failed, 0 if it happens during the first duplicate
//                   1 if it happens after the first duplicate
// ERR_CMD_PIPE  : pipe failed
// ERR_CMD_FAILED: excve didn't execute the command
typedef enum e_error
{
	GOOD,
	ERR_ALLOC,
	ERR_CMD_NOARG,
	ERR_CMD_DUP0,
	ERR_CMD_DUP1,
	ERR_CMD_PIPE,
	ERR_CMD_FAIL
}	t_error;
#endif