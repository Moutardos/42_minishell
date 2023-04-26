/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:34:18 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/26 14:14:56 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"

// Je sais pas si c'est interessant de mettre la variable env
// en global, pour un acces facile
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_arg
{
	int				ac;
	const char		**av;
	int				pipe[2];
	int				is_piped;
	struct s_arg	*next;
	struct s_arg	*previous;
}  t_arg;

typedef struct s_minishell
{
	t_env	env;
	char	*pwd;
	char	*raw_line;
	t_arg	*args;
}  t_minishell;

#endif