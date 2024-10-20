#include "get_next_line.h"
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *concat_str(char *buffer, char *stash);
size_t  ft_strlen(char *str);

char	*if_new_line(char *buffer, char *stash, int bytes_read) //return stash
{
	int	i;
	int	len_buffer;

	i = 0;
	if (!buffer)
		return (NULL);
	len_buffer = ft_strlen(buffer);
	while (buffer[i])
        {
                if (buffer[i] == '\n')
			stash = ft_substr(buffer, i + 1, len_buffer - i - 1);
		else
			i++;
        }
	
	return (stash);
}

char	*get_next_line(fd)
{
	static char	*stash;
	char	*buffer;
	int	bytes_read;

	stash = NULL;
	buffer = NULL;
	if (stash)
        {
                buffer = concat_str(buffer, stash);
        }
	if (fd == -1)
		return (NULL);
	if (fd == 0)
		buffer[0] = '\0';
	bytes_read = 0;
        stash = if_new_line(buffer, stash, bytes_read); //to get previous stash
        printf("check stash: %s\n", stash);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1 || bytes_read == 0)
		return (NULL);
	return (buffer);
}

int     main(void)
{
        int     fd;
        char *line;

        fd = open("one_line.txt", O_RDONLY);
        printf("num fd: %i\n", fd);
        if (fd == -1)
                return 1;
        //line = get_next_line(fd);
        while ((line=get_next_line(fd)) != NULL)
        {
		printf("\nentra loop\n");
                printf("%s\n", line);
                free(line);
        }
        close(fd);
        return (0);
}
