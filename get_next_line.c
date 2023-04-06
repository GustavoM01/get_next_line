/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaldona <gmaldona@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:10:08 by gmaldona          #+#    #+#             */
/*   Updated: 2023/04/06 15:23:30 by gmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_bookmark	bookmark[BOOKMARK_SIZE];
	char				*buffer;
	int					found_nl;
	int					j;
	int					bm_i;

	found_nl = 0;
	buffer = NULL;
	j = 0;
	bm_i = 0;
	if (fd > -1)
	{
		buffer = bookmark_manager(bookmark, fd, &bm_i);
		if (buffer)
			return (buffer);
		buffer = read_mng(fd, (bookmark + bm_i));
	}
	return (buffer);
}
