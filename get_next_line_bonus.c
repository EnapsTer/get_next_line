/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:23:28 by aherlind          #+#    #+#             */
/*   Updated: 2020/11/10 16:23:31 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
//#define BUFFER_SIZE 42


int 	index_of_char(char *s, char c)
{
	int index;

	index = -1;
	while (s[++index])
		if (s[index] == c)
			return (index);
	return (-1);
}


int		add_buf_to_line(char **buffer, char **line)
{
	int 	char_index;
	char	*tmp;

	if ((char_index = index_of_char(*buffer, '\n')) != -1)
	{
		(*buffer)[char_index] = '\0';
		*line = ft_gnl_strdup(*buffer);
		tmp = *buffer;
		*buffer = ft_gnl_strdup(*buffer + char_index + 1);
		free(tmp);
		return (char_index);
	}
	else
	{
		*line = ft_gnl_strdup(*buffer);
		free(*buffer);
	}
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static char	*buffers[1024];
	char		*s;
	int 		chars_read;
	int			char_index;

	chars_read = 1;
	*line = NULL;
	char_index = -1;
	s = (char *)malloc(BUFFER_SIZE + 1);
	if (buffers[fd])
		char_index = add_buf_to_line(&buffers[fd], line);
	while (char_index == -1 && chars_read > 0)
	{
		chars_read = read(fd, s, BUFFER_SIZE);
		if (chars_read < 0)
		{
			free(s);
			return (-1);
		}
		s[chars_read] = '\0';
		if ((char_index = index_of_char(s, '\n')) >= 0)
		{
			s[char_index] = '\0';
			buffers[fd] = ft_gnl_strdup(s + char_index + 1);
		}
		*line = ft_gnl_strjoin(*line, s);
	}
	if (!chars_read)
		buffers[fd] = NULL;
	if (s)
		free(s);
	return (chars_read ? 1 : 0);
}