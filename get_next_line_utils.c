/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaldona <gmaldona@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:46:34 by gmaldona          #+#    #+#             */
/*   Updated: 2023/03/20 17:12:29 by gmaldona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_next_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*fnl(char *buffer)
{

}

char	*line_buffer(char *buffer, t_bookmark *bm, int found_nl)
{
	int		i;
	int		j;
	char	*line_buffer;

	i = 0;
	j = 0;
	line_buffer = (char *) malloc(sizeof(char) * found_nl + 1);
	line_buffer[found_nl] = '\0';
	while (i < (found_nl))
	{
		line_buffer[i] = buffer[i];
		i++;
	}
	while (buffer[i] != '\0')
	{
		bm[0].remainder[j] = buffer[i];
		i++;
	j++;
	}
	bm[0].remainder[i] = '\0';
	bm[0].size = j - 1;
	if (buffer)
		free(buffer);
	return (line_buffer);
}

int	bookmark_manager(t_bookmark *bookmark, int fd)
{
	int i;

	i = 1;
	if (bookmark[0].init != 'Y' && bookmark[0].fd != -1)
	{
		bookmark[0].init = 'Y';
		bookmark[0].fd = -1;
		while (i < BOOKMARK_SIZE)
		{
			bookmark[i].init = 'N';
			bookmark[i].eof = 'N';
			bookmark[i].size = 0;
			i++;
		}
	}
	i = 1;
	while (bookmark[i].init == 'Y')
	{
		if (bookmark[i].fd == fd)
			return (i);
		i++;
	}
	bookmark[i].init = 'Y';
	bookmark[i].fd = fd;
	bookmark[i].remainder[0] = '\0';
	bookmark[i].size = 0;
	return (i);
}


static	char	*read_manager(int fd, char *buffer, int multiplier, int shift, t_bookmark *bm)
{
	char	*inc_buffer;
	int		i;
	int		j;
	size_t	bytes_read;

	i = 0;
	j = 0;
	bytes_read = 0;
	inc_buffer = (char *) malloc(sizeof(char) * ((BUFFER_SIZE * multiplier)  + shift + 1));
	if (!inc_buffer)
		return (NULL);
	while (bm[0].remainder[i] != '\0')
	{
		inc_buffer[i] = bm[0].remainder[i];
		bm[0].remainder[i] = '\0';
		i++;
	}
	if (bm[0].remainder[0] == '\0')
		bm[0].size = 0;
	if (buffer)
	{
		while (buffer[j] != '\0')
		{
			inc_buffer[i] = buffer[j];
			i++;
			j++;
		}
		inc_buffer[i] = '\0';
		free(buffer);
	}
	bytes_read = read(fd, inc_buffer + i, BUFFER_SIZE);
	if (bytes_read == 0 || bytes_read == (size_t) -1)
	{
		if (bytes_read == 0)
		{
			bm[0].eof = 'Y';
			if (multiplier == 1)
			{
				free(inc_buffer);
				return (NULL);
			}
		}
		if (inc_buffer[0] != '\0')
			return (inc_buffer);
		free(inc_buffer);
		return (NULL);
	}
	inc_buffer[i + bytes_read] = '\0';
	if (bytes_read < BUFFER_SIZE)
		bm[0].eof = 'Y';
	return (inc_buffer);
}

/**
 * @brief This will return a line, which size is unknown.
 * It uses read() as many times as it takes to find '\n' or EOF.
 *
 * @param fd the file descripter used by read(). It should be a valid file descriptor.
 * @param bookmark bookmark struct with fd information.
 * @param found_nl where and if '\n' is found in the line.
 * A pointer is used to update this value in main function.
 * @return char* that points to line.
 */
char	*get_line(int fd, t_bookmark *bookmark, int *found_nl)
{
	char	*buffer;
	int		shift;
	int		multiplier;
	int		i;
	int		j;

	shift = 0;
	multiplier = 1;
	buffer = NULL;
	i = 0;
	j = 0;
	if (bookmark[0].remainder[0] != '\0')
		shift += bookmark[0].size;
	while (*found_nl == 0 && bookmark[0].eof != 'Y')
	{
		buffer = read_manager(fd, buffer, multiplier, shift, bookmark);
		if (!buffer)
			return (NULL);
		*found_nl = find_next_line(buffer);
		multiplier++;
	}
	return (buffer);
}

/**
 * @brief
 *
 * @param bm
 * @return char* with pointer to memory containing new line or null if no new line is found.
 */
char	*find_bm_line(t_bookmark *bm)
{
	char	*buffer;
	int		i;
	int		j;

	buffer = NULL;
	j = 0;
	if ((i = find_next_line(bm[0].remainder)))
	{
		buffer = (char *) malloc((sizeof(char) * i) + 2);
		if (buffer)
		{
			buffer[i] = '\0';
			buffer[i - 1] = '\n';
			while (j < (i - 1))
			{
				buffer[j] = bm[0].remainder[j];
				j++;
			}
			i++;
			j = 0;
			while (bm[0].remainder[i] != '\0')
			{
				bm[0].remainder[j] = bm[0].remainder[i];
				i++;
				j++;
			}
			j++;
			bm[0].remainder[j] = '\0';
			bm[0].size = j;
		}
	}
	return (buffer);
}
