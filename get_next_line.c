#include "get_next_line.h"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

size_t  ft_strlen(char *str);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *concat_str(char *buffer, char *stash);
char    *ft_strdup(char *s);
char    *ft_strchr(char *s, char ch);

char	*fill_in_line(char **stash)
{
	char	*pos_n;
	char	*line;
	int	len_stash;

	if (!*stash)
		return (NULL);
	len_stash = (int)ft_strlen(*stash);
	line = NULL;
	pos_n = ft_strchr(*stash, '\n');
	if (!pos_n)
	{
		line[len_stash] = '\0';
		line = ft_strdup(*stash);
	}
	line = ft_substr(*stash, pos_n - *stash, len_stash - (pos_n - *stash));
	return (line);
}
/*
int	read_buffer_size(int *fd, char *buffer)
{
	
}
*/
char	*get_next_line(int fd)
{
	static char	*stash;
	char	*buffer;
	int	bytes_read;
	char	*second_buffer;
	char	*total_buffer;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	//printf("\nbytes_read :%i\n", bytes_read);
	if (bytes_read == -1)
                return (NULL);
	buffer[bytes_read] = '\0';
	//printf("\nfirst buffer:%s\n", buffer);
	while (bytes_read > 0)
	{
		char	*check = ft_strchr(buffer, '\n');
		//printf("\ncheck: %s", check);
		if (check != NULL)
		{
			stash = ft_substr(buffer, 0, check - buffer);
			break ;
		}
		else
		{
			second_buffer = (char *)malloc(BUFFER_SIZE + 1);
			if (!second_buffer)
				return (NULL);
			bytes_read = read(fd, second_buffer, BUFFER_SIZE);
			second_buffer[bytes_read] = '\0';
			total_buffer = (char *)malloc(sizeof(buffer) + sizeof(second_buffer) + 1);
			if (!total_buffer)
				return (NULL);
			total_buffer = concat_str(buffer, second_buffer);
			free(buffer);
			free(second_buffer);
			//printf("\n\nsecond bytes__read: %d", bytes_read);
		}
	}
	if (!buffer || !stash)
	{
		free(buffer);
		free(stash);
		return (NULL);
	}
	printf("\ncheck stash: %s", stash);
	return (fill_in_line(&stash));
}

int	main(void)
{
	int	fd;
	char *line;

	fd = open("one_line.txt", O_RDONLY);
	//printf("num fd: %i\n", fd);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("\nfinal: %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
