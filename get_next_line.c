/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaldona <gmaldona@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:10:08 by gmaldona          #+#    #+#             */
/*   Updated: 2023/03/20 17:12:25 by gmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_bookmark	bookmark[BOOKMARK_SIZE];
	int					i;
	char				*buffer;
	int					found_nl;
	int					j;

	found_nl = 0;
	buffer = NULL;
	j = 0;
	if (fd > -1)
	{
		i = bookmark_manager(bookmark, fd);
		if (bookmark[i].size > 0)
		{
			if ((found_nl = find_next_line(bookmark[i].remainder)))
				buffer = find_bm_line(bookmark + i);
			else if (bookmark[i].eof == 'Y')
			{
				buffer = (char *) malloc(sizeof(char) * bookmark[i].size);
				while (bookmark[i].remainder[j] != '\0')
				{
					buffer[j] = bookmark[i].remainder[j];
					j++;
				}
			}
		}
		if (buffer == NULL && bookmark[i].eof == 'N')
		{
			buffer = get_line(fd, bookmark + i, &found_nl);
			if (buffer != NULL)
			{
				if (bookmark[i].eof != 'Y' && found_nl > 0)
					buffer = line_buffer(buffer, bookmark + i, found_nl);
			}
		}
	}
	return (buffer);
}
