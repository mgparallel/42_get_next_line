/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: menwu <menwu@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:42:09 by menwu             #+#    #+#             */
/*   Updated: 2024/10/30 17:45:46 by menwu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_storage(char **storage)
{
	free(*storage);
	*storage = NULL;
	return (NULL);
}

char	*read_buffer(int fd, char **stash)
{
	char	*new_str;
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (free(buffer), *stash);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		new_str = ft_strjoin(*stash, buffer);
		free(*stash);
		if (!new_str)
			return (free(buffer), NULL);
		*stash = new_str;
		if (ft_strchr(new_str, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (*stash);
}

char	*get_line(char **stash)
{
	char	*line;
	char	*pos;

	if (!*stash || *stash == (void *)0)
		return (NULL);
	pos = ft_strchr(*stash, '\n');
	if (!pos)
		return (ft_strdup(*stash));
	line = ft_substr(*stash, 0, pos - *stash + 1);
	if (!line)
		free_storage(stash);
	return (line);
}

char	*update_stash(char **stash)
{
	char	*pos;
	char	*new_stash;

	if (!*stash)
		return (NULL);
	pos = ft_strchr(*stash, '\n');
	if (!pos)
		return (free_storage(stash));
	new_stash = ft_strdup(pos + 1);
	free(*stash);
	*stash = new_stash;
	if (!*stash)
		return (free_storage(stash));
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		*temp_stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if ((stash && !ft_strchr(stash, '\n')) || !stash)
	{
		temp_stash = read_buffer(fd, &stash);
		if (!temp_stash)
			return (free_storage(&stash));
		stash = temp_stash;
	}
	if (*stash == '\0')
		return (free_storage(&stash));
	line = get_line(&stash);
	if (!line)
		return (free_storage(&stash));
	stash = update_stash(&stash);
	return (line);
}
