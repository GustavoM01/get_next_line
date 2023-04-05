/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaldona <gmaldona@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:46:34 by gmaldona          #+#    #+#             */
/*   Updated: 2023/04/05 15:51:06 by gmaldona         ###   ########.fr       */
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
			*index = i;
			return (i);
		}
		i++;
	}
	*index = 0;
	return (0);
}

char	*fnl(char *buffer, char isBm)
{
	int		i;
	int		j;
	char	*line;

	i = -1;
	j = 0;
	line = (char *) malloc((sizeof(char) * BOOKMARK_SIZE) + 1);
	while (buffer[++i] != '\0' && line && buffer[i] != '\n')
		line[i] = buffer[i];
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else if (line)
	{
		free(line);
		line = NULL;
	}
	if (isBm == 'Y')
	return (line);
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

char	*bookmark_manager(t_bookmark *bm, int fd, int *bm_i)
{
	int		nl_i;
	char	*buffer;
	int		cpy_nl_i;

	buffer = NULL;
	while (bm[*bm_i].fd > 0 && bm[*bm_i].fd != fd)
		*bm_i++;
	if (bm[*bm_i].fd == fd && find_nl(bm[*bm_i].remainder, &nl_i))
	{
		buffer = (char *) malloc(sizeof(char) * (nl_i + 2));
		if (buffer)
		{
			cpy_nl_i = nl_i;
			buffer[nl_i + 1] = '\0';
			while (nl_i-- > -1)
				buffer[nl_i] = bm[*bm_i].remainder[nl_i];
			while (++cpy_nl_i < bm[*bm_i].size && nl_i++)
				bm[*bm_i].remainder[nl_i] = bm[*bm_i].remainder[cpy_nl_i];
			bm[*bm_i].size = nl_i + 1;
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

	i = 0;
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
		{
			free(buffer);
			if (bm[0].size == 0 || read_bytes == -1)
				return (NULL);
			buffer = (char *) malloc(sizeof(char) * (bm[0].size + 1));
			while (bm[0].remainder[i++])
				buffer[i] = bm[0].remainder[i];
			bm[0].remainder[0] = '\0';
			bm[0].size = 0;
		}
		else if (find_nl(buffer, &i))
			buffer = get_buffer_line(buffer, bm, i);
		else
			buffer = keep_reading(fd, buffer, bm);
	}
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
	buf_size = found_nl + 2 + bm[0].size;
	line_buffer = (char *) malloc(sizeof(char) * buf_size);
	if (line_buffer)
	{
		line_buffer[buf_size - 1] = '\0';
		while (++i < bm[0].size)
			line_buffer[i] = bm[0].remainder[i];
		while (i <= (buf_size - 2))
			line_buffer[i++] = buffer[j++];
		i = 0;
		while (buffer[j] != '\0')
			bm[0].remainder[i++] = buffer[j++];
		bm[0].remainder[++i] = '\0';
		bm[0].size = i - 1;
		free(buffer);
	}
	return (line_buffer);
}

char	*keep_reading(int fd, char *buffer, t_bookmark *bm)
{
		int		i;
	int		j;
	char	*line_buffer;
	int		buf_size;

	i = -1;
	j = 0;
	buf_size = found_nl + 2 + bm[0].size;
	line_buffer = (char *) malloc(sizeof(char) * buf_size);
	if (line_buffer)
	{
		line_buffer[buf_size - 1] = '\0';
		while (++i < bm[0].size)
			line_buffer[i] = bm[0].remainder[i];
		while (i <= (buf_size - 2))
			line_buffer[i++] = buffer[j++];
		i = 0;
		while (buffer[j] != '\0')
			bm[0].remainder[i++] = buffer[j++];
		bm[0].remainder[++i] = '\0';
		bm[0].size = i - 1;
		free(buffer);
	}
	return (line_buffer);
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
		*found_nl = find_nl(buffer, &i);
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
	i = find_nl(bm[0].remainder, &i);
	if (i)
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
