#include "get_next_line.h"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *concat_str(char *buffer, char *stash);

char	*if_new_line(char *buffer, int bytes_read)
{
	static char	*stash;
	int 	i;
	size_t	position_n;
	size_t	bytes_stash;

	i = 0;
	position_n = 0;
	bytes_stash = 0;
	stash = NULL;
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
	if (bytes_stash == 0)
	{
		buffer = ft_substr(buffer, 0, i);
		return (NULL);
	}
	while (buffer[i++])
	{
		*stash = buffer[i];
		stash++;
	}
	return (stash);
}

char	*return_buffer(char *buffer, char *stash)
{
	if (stash)
		buffer = concat_str(buffer, stash);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	int	bytes_read;
	char	*stash;
	
	if (fd == -1 || fd == 0) //come back here fd = 0 should be corner case
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	printf("\nbytes_read :%i\n", bytes_read);
	if (bytes_read == -1)
	{
		printf("bytes read -1, error!\n");
                return (NULL);
	}
	/*if (bytes_read == 0)
                */
	if (bytes_read > 0)
	{
		stash = if_new_line(buffer, bytes_read);
		printf("\ncheck stash: %s\n", stash);
		if (stash == NULL)
			get_next_line(fd);
		else
			buffer = return_buffer(buffer, stash);
	}
	return (buffer);
}

int	main(void)
{
	int	fd;
	char *line;

	fd = open("one_line.txt", O_RDONLY);
	printf("num fd: %i\n", fd);
	if (fd == -1)
		return 1;
	//line = get_next_line(fd);
	while ((line=get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
