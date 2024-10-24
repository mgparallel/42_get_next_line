#include "get_next_line.h"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

size_t  ft_strlen(char *str);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_strdup(char *s);
int    ft_strchr(char *s, char ch);

char	*fill_in_line(char **stash)
{
	int	pos_n;
	char	*line;
	int     len_stash;
        char    *new_stash;

       	if (!*stash)
        {
		return (NULL);
        }
        len_stash = (int)ft_strlen(*stash);
        pos_n = ft_strchr(*stash, '\n');
        if (pos_n == 0) // when no new line found
        {
		/*if (len_stash == 0)
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}*/
                line = ft_strdup(*stash);
		free(*stash);
                *stash = NULL;
		return (line);
        }
        else
        {
                line = ft_substr(*stash, 0, pos_n + 1);
                new_stash = ft_substr(*stash, pos_n + 1, len_stash - pos_n);
                free(*stash);
                *stash = new_stash;
		return (line);
	}
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char	*buffer;
	int	bytes_read;

	if (fd == -1 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (ft_strchr(stash, '\n') != 0) //when newline found in buffer
		{
			//free(stash);
			break ;
		}
		else //NO new line found
		{
			free(buffer);
			buffer = (char *)malloc(BUFFER_SIZE + 1);
			if (!buffer)
			{
				free(stash);
				return (NULL);
			}
			bytes_read = read(fd, buffer, BUFFER_SIZE);
		}
	}
	free(buffer);
	if (bytes_read < 0 || (bytes_read == 0 && (!stash || *stash == '\0')))
	{	
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (fill_in_line(&stash));
}

int     main(void)
{
        int     fd;
        char *line;

        fd = open("one_line.txt", O_RDONLY);
        //printf("num fd: %i\n", fd);
        if (fd == -1)
                return (1);
        while ((line = get_next_line(fd)) != NULL)
        {
                printf("%s", line);
                free(line);
        }
        close(fd);
        return (0);
}
