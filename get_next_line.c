#include "get_next_line.h"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

size_t  ft_strlen(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strjoin(char *s1, char *s2, char *total_buffer);
//char    *concat_str(char *buffer, char *stash);
char    *ft_strdup(char *s, char *result);
int    ft_strchr(char *s, char ch);

char	*fill_in_line(char **stash)
{
	int 	pos_n;
	char	*line;
	int	len_stash;
	char	*new_stash;

	if (!*stash)
	{
		*stash = malloc(1);
		**stash = '\0';
	}	
	len_stash = (int)ft_strlen(*stash);
	pos_n = ft_strchr(*stash, '\n');
	printf("VALUE POS_N: %d", pos_n);
	if (pos_n == 0)
	{
		line = (char *)malloc(len_stash + 1);
		line = ft_strdup(*stash, line);
		*stash = NULL;
	}
	else
	{
		line = ft_substr(*stash, 0, pos_n + 2);
		new_stash = ft_substr(*stash, pos_n + 1, len_stash - pos_n + 1);
		free(*stash);
		new_stash[len_stash - pos_n] = '\0';
		*stash = new_stash;
	}
	printf("\n\ntest line: %s", line);
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
		if (total_buffer != NULL)
			buffer = total_buffer;
		printf("\nCHECK buffer:%s\n", buffer);
		if (ft_strchr(buffer, '\n') != 0)
		{
			stash = ft_substr(buffer, 0, (size_t)(ft_strchr(buffer, '\n')));
			break ;
		}
		else
		{
			second_buffer = (char *)malloc(BUFFER_SIZE + 1);
			if (!second_buffer)
				return (NULL);
			bytes_read = read(fd, second_buffer, BUFFER_SIZE);
			//printf("\n\nBYTES: %d", bytes_read);
			second_buffer[bytes_read] = '\0';
			total_buffer = (char *)malloc(ft_strlen(buffer) + bytes_read + 1);
			if (!total_buffer)
				return (NULL);
			printf("\nsecond buffer: %s", second_buffer);
			total_buffer = ft_strjoin(buffer, second_buffer, total_buffer);
			//printf("\n\nTOTAL Buffer: %s", total_buffer);
			free(second_buffer);
		}
	}
	/*if (!buffer || !stash)
	{
		free(buffer);
		free(stash);
		return (NULL);
	}*/
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
		printf("\niteration: %d", fd);
		printf("\nfinal: %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
