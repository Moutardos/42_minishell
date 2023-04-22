/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcozdenm <lcozdenm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 06:59:19 by lcozdenm          #+#    #+#             */
/*   Updated: 2023/01/30 14:58:10 by lcozdenm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif
# ifdef BUFFER_SIZE 
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

/* Store every character read in the file until a newline is met */
typedef struct s_line
{
	ssize_t			size;
	char			buf[BUFFER_SIZE + 1];
	struct s_line	*next;
}	t_line;

/* Link to keep the first fd struct*/
typedef struct s_ffd
{
	struct s_fd	*first;
}	t_ffd;

/* Regroup each file director with his lines buffer, reste contains character
 found in the last line buffer after the newline*/
typedef struct s_fd
{
	int			fd;
	char		reste[BUFFER_SIZE + 1];
	t_line		*lines;
	struct s_fd	*next;
}	t_fd;

/** MAIN **/

/* Return the next line in the fd file */
char	*get_next_line(int fd);

/* Fills the buffer of one line node */
t_line	*get_line(t_fd *fdinfo);

/* Fills node of line until met with a newline */
t_line	*fill_lines(t_fd *fdinfo, ssize_t *nsize);

/* Create a character string made of all the buffer from the struct line */
char	*make_real_line(t_fd *fdinfo, ssize_t size);

/* Create a struct that point to the first struct fd*/
t_ffd	*init_fdinfos(t_ffd *fdinfos);
/** UTILS **/

/* Get the file director struct from the file director in parameter, create
   one if not there*/
t_fd	*get_new_fd(int fd, t_ffd **fdinfo);

/* Free file director struct */
void	free_fd(int fd, t_ffd **fd_infos);

/* Free line struct*/
void	free_line(t_line **line);

/* Return index ft_strchrof where character c is found, -1 if absent*/
ssize_t	ft_strchr2(const char *s, int c);

/* Fills the character found after a newline in the line buffer,
   is printed first when get_next_line is called*/
void	fill_reste(t_fd *fdinfo, t_line *line);
#endif
