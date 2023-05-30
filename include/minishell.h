/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coltcivers <coltcivers@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:34:18 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/05/29 10:02:21 by coltcivers       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

#include <limits.h>

# include "handlers.h"
# include "libft/libft.h"
# include "error.h"
# include "parsing.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 100 // pour pwd, jsp quoi mettre

typedef enum e_delim
{
  IN,
  OUT,
  IN_NL,
  OUT_APPEND,
  NONE
} t_delim;

// path = chemin du prog, allocated par check_paths dans files_utils
typedef struct s_cmd
{
	int				ac;
	char			**av;
	int				in;
	int				out;
	t_delim			*delim;
	char			**delim_f;
	int				heredoc;
	char			*fname;
	char			*path;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	int				delim_amount;
}  t_cmd;

//exit code else than 0 = process spinning down
//paths = $paths de l'environement de l'user, allocated par str_split
typedef struct s_minishell
{
	t_dico	*env;
	char	**paths;
	char	pwd[BUFFER_SIZE];
	char	*raw_line;
	t_cmd	*cmds;
	int		exit;
}  t_minishell;

#endif