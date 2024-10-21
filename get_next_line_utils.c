#include <stddef.h>
#include <stdlib.h>
size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
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
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len-- > 0)
	{
		result[len] = s[start + len];
	}
	return (result);
}

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
}

char	*ft_strchr(char *s, char ch)
{
	char	*ref;

	ref = s;
	while (*ref)
	{
		if (*ref == ch)
			break ;
		ref++;
	}
	return (*ref);
}

char	*ft_strdup(char *s)
{
	char	*temp;
	char	*result;

	temp = s;
	while (*temp)
	{
		*result = *temp
		temp++;
	}
	return (result);
}
