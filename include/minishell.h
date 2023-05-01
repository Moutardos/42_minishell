/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:34:18 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/01 13:18:35 by lcozdenm         ###   ########.fr       */
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

typedef struct s_cmd
{
	int				ac;
	const char		**av;
	int				pipe[2];
	int				in;
	int				out;
	t_delim			delim;
	char			*delim_f;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}  t_cmd;

typedef struct s_minishell
{
	t_env	env;
	char	*pwd;
	char	*raw_line;
	t_cmd	*args;
	int		exit;
}  t_minishell;

#endif