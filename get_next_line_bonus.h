/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaldona <gmaldona@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:30:46 by gmaldona          #+#    #+#             */
/*   Updated: 2023/04/29 16:39:15 by gmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# ifndef BOOKMARK_SIZE
#  define BOOKMARK_SIZE 20
# endif
# include <unistd.h>
# include <stdlib.h>

typedef struct s_bookmark
{
	int		fd;
	char	rmd[BUFFER_SIZE + 1];
	int		size;
}	t_bookmark;

char	*get_next_line(int fd);
char	*bookmark_manager(t_bookmark *bookmark, int fd, int *bm_i);
char	*read_mng(int fd, t_bookmark *bm);

#endif