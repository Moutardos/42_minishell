/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:34:18 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/04/28 16:56:12 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
#include <limits.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

// Je sais pas si c'est interessant de mettre la variable env
// en global, pour un acces facile
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_delim
{
  IN,
  OUT,
  IN_NL,
  OUT_APPEND,
  NONE
} t_delim;

typedef struct s_arg
{
	int				ac;
	const char		**av;
	int				pipe[2];
	t_delim			delim;
	char			*delim_f;
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
	int		exit;
}  t_minishell;

#endif