/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaldona <gmaldona@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:46:34 by gmaldona          #+#    #+#             */
/*   Updated: 2023/04/29 15:59:21 by gmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/**
 * @brief it works in 2 ways, it returns value, so it can be used in control
 * structures and also assigns by reference to be able to store the value if
 * function is used in control structure.
 *
 * @param buffer char * to search for '\n'
 * @param index pointer to assign if '\n' is found, else assigns 0;
 * @return index of '\n' if found, else return 0;
 */
int	find_nl(char *buffer, int *index)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			*index = i + 1;
			return (1);
		}
		i++;
	}
	*index = i + 1;
	return (0);
}

char	*bookmark_manager(t_bookmark *bm, int fd, int *bm_i)
{
	char	*buffer;
	int		nl_i;
	int		cpy_nl_i;

	buffer = NULL;
	while (bm[*bm_i].fd > 0 && bm[*bm_i].fd != fd)
		(*bm_i)++;
	if (bm[*bm_i].fd == fd && bm[*bm_i].size && find_nl(bm[*bm_i].rmd, &nl_i))
	{
		buffer = (char *) malloc(sizeof(char) * (nl_i + 1));
		if (buffer)
		{
			cpy_nl_i = nl_i - 1;
			buffer[nl_i] = '\0';
			while (--nl_i > -1)
				buffer[nl_i] = bm[*bm_i].rmd[nl_i];
			while (++cpy_nl_i < bm[*bm_i].size)
				bm[*bm_i].rmd[++nl_i] = bm[*bm_i].rmd[cpy_nl_i];
			bm[*bm_i].size = nl_i + 1;
			bm[*bm_i].rmd[nl_i + 1] = '\0';
		}
	}
	else
		bm[*bm_i].fd = fd;
	return (buffer);
}

char	*read_mng(int fd, t_bookmark *bm)
{
	int		read_bytes;
	char	*buffer;
	int		i;

	i = -1;
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	buffer[read_bytes] = '\0';
	if (read_bytes < BUFFER_SIZE && find_nl(buffer, &i) == 0)
	{
		if (read_bytes <= 0 && bm[0].size == 0)
		{
			free(buffer);
			return (NULL);
		}
		if (read_bytes == 0)
			read_bytes++;
		buffer = get_buffer_line(buffer, bm, read_bytes);
	}
	else if (find_nl(buffer, &i) || (read_bytes < BUFFER_SIZE && bm[0].size > 0))
		buffer = get_buffer_line(buffer, bm, i);
	else
		buffer = keep_reading(buffer, bm, 2, BUFFER_SIZE);

	return (buffer);
}

char	*get_buffer_line(char *buffer, t_bookmark *bm, int found_nl)
{
	int		i;
	int		j;
	char	*line_buffer;
	int		buf_size;

	i = -1;
	j = 0;
	if (found_nl == 0)
		return (buffer);
	buf_size = found_nl + 1 + bm[0].size;
	line_buffer = (char *) malloc(sizeof(char) * buf_size);
	if (line_buffer)
	{
		line_buffer[buf_size - 1] = '\0';
		while (++i < bm[0].size)
			line_buffer[i] = bm[0].rmd[i];
		while (i <= (buf_size - 2))
			line_buffer[i++] = buffer[j++];
		i = 0;
		while (buffer[j] != '\0' && buffer[j - 1] != '\0')
			bm[0].rmd[i++] = buffer[j++];
		bm[0].rmd[i] = '\0';
		bm[0].size = i;
		free(buffer);
	}
	return (line_buffer);
}

char	*keep_reading(char *buf, t_bookmark *bm, int mlt, int b_size)
{
	int		i;
	char	*inc_buf;
	int		index;
	int		read_bytes;

	i = -1;
	index = 0;
	b_size += BUFFER_SIZE;
	inc_buf = (char *) malloc(sizeof(char) * (b_size + 1));
	while ((++i) < (b_size - BUFFER_SIZE))
		inc_buf[i] = buf[i];
	inc_buf[b_size] = '\0';
	read_bytes = read(bm[0].fd, inc_buf + i, BUFFER_SIZE);
	if (find_nl(inc_buf, &index) == 0 && read_bytes > 0)
		inc_buf = keep_reading(inc_buf, bm, ++mlt, b_size);
	else if (read_bytes == 0)
	{
		free(inc_buf);
		return (buf);
	}
	else
		inc_buf = get_buffer_line(inc_buf, bm, index);
	free(buf);
	return (inc_buf);
}
