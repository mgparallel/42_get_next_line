#include "get_next_line_bonus.h"

int 	main(int ac, char **av)
{
	int	fd;
	char 	*str;
	int	i = 1;
	
	if (ac < 2)
		return (1);
	while (av[i])
	{
		fd = open(av[i], O_RDONLY);
		if (fd == -1)
		{	
			printf("Error opening file");
			return (1);
		}
		printf("\nReading a file\n");
		while ((str = get_next_line(fd)) != NULL)
		{
			printf("%s", str);
			free(str);
		}
		close(fd);
		i++;
	}
	return (0);
}
