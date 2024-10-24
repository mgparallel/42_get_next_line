#include <stddef.h>
#include <stdlib.h>
size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
		len++;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*result;
	size_t		total_len;

	if (!s)
		return (NULL);
	total_len = ft_strlen((char *)s);
	if (start > total_len - 1)
		len = 0;
	else if (start + len > total_len)
		len = total_len - start;
	result = (char *)malloc((len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len-- > 0)
	{
		result[len] = s[start + len];
	}
	return (result);
}

char    *ft_strjoin(char *s1, char *s2)
{
        int     i;
        int     j;
	char	*result;

	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
        if (!result)
		return (NULL);
	i = 0;
        j = 0;
        while (i < (int)ft_strlen(s1))
        {
                result[i] = s1[i];
                i++;
        }
        while (j < (int)ft_strlen(s2))
        {
                result[i + j] = s2[j];
                j++;
        }
        result[i + j] = '\0';
        return (result);
}
/*
char	*concat_str(char *buffer, char *stash)
{
	int	i;
	int	j;
	int	len_buffer;
	int	len_stash;
	char	*result;

	result = (char *)malloc(sizeof(stash) + sizeof(buffer) + 1); //need free
	if (!result)
		return (NULL);
	len_buffer = ft_strlen(buffer);
	len_stash = ft_strlen(stash);
	i = -1;
	j = -1;
	while (++i < len_buffer)
		result[i] = buffer[i];
	while (++j < len_stash)
		result[i + j] = stash[j];
	result[i + j] = '\n';
	return (result);
}*/

int	ft_strchr(char *s, char ch)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			break ;
		i++;
	}
	if (s[i] == '\0')
		return (0);
	return (i);
}

char	*ft_strdup(char *s)
{
	int	i;
	char	*result;

	result = (char *)malloc(ft_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
