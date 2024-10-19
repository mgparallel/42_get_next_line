#include "get_next_line.h"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *concat_str(char *buffer, char *stash, size_t bytes_stash);

size_t	if_new_line(int fd, char *buffer, int bytes_read, char *stash)
{
	int 	i;
	size_t	position_n;
	size_t	bytes_stash;

	i = 0;
	position_n = 0;
	bytes_stash = 0;
	while (buffer[i])
	{
		if (buffer[i] != '\n')
			position_n += sizeof(buffer[i]);
		else
		{
			bytes_stash += bytes_read - position_n - 1;
			stash = (char *)malloc(bytes_stash);
			break ;
		}
		i++;
	}
	if (i == bytes_read)
	{
		stash = ft_substr(stash, 0, i);
		get_next_line(fd);
	}
	while (buffer[i++])
	{
		*stash = buffer[i];
		stash++;
	}
	return (bytes_stash);
}

char	*return_buffer(size_t position_n, char *buffer, char *stash)
{
	if (stash)
		buffer = concat_str(buffer, stash, position_n);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char	*buffer;
	int	bytes_read;
	size_t	position_n;
	
	if (fd == -1 || fd == 0) //come back here fd = 0 should be corner case
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	printf("\nbytes_read :%i\n", bytes_read);
	if (bytes_read == -1)
	{
		printf("bytes read\n");
                return (NULL);
	}
	/*if (bytes_read == 0)
                */
	stash = NULL;
	if (bytes_read > 0)
	{
		position_n = if_new_line(fd, buffer, bytes_read, stash);
		printf("FLAG!%zu", position_n);
		buffer = return_buffer(position_n, buffer, stash);
	}
	return (buffer);
}

int	main(void)
{
	int	fd;
	char *line;

	fd = open("one_line.txt", O_RDONLY);
	printf("num fd%i\n", fd);
	if (fd > 0)
		line = get_next_line(fd);
	else
		line = NULL;
	while (line)
	{
		//printf("entro main\n");
		printf("%s\n", line);
		//result = get_next_line(fd);
	}
	free (line);
	return (0);
}
