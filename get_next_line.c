#include "get_next_line.h"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *concat_str(char *buffer, char *stash);
char    *ft_strdup(char *s);
char    *ft_strchr(char *s, char ch);

char	*fill_in_line(char **stash)
{
	char	*pos_n;
	char	*line;

	pos_n = ft_strchr(&stash, '\n');
	if (!pos_n)
	{
		//line[end] = '\0';
		line = ft_strdup(&stash);
		break ;
	}
	line = ft_substr(&stash, pos_n, pos_n - &stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char	*buffer;
	int	bytes_read;
	int	i;
	
	if (fd == -1 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	printf("\nbytes_read :%i\n", bytes_read);
	if (bytes_read == -1)
                return (NULL);
	i = 0;
	while (bytes_read > 0)
	{
		if (ft_strchr(buffer, '\n') != NULL)
		{
			stash = concat_str(stash, ft_strchr(buffer, '\n'));
			break;
		}
		else
			read(fd, buffer, BUFFER_SIZE);
	}
	return (fill_in_line());
}

int	main(void)
{
	int	fd;
	char *line;

	fd = open("one_line.txt", O_RDONLY);
	printf("num fd: %i\n", fd);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
