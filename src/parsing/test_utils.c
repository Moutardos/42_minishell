#include "../../include/minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			count;
	size_t			i;
	unsigned char	*alloc;

	if (nmemb > SIZE_MAX / size)
        	return (NULL);
	count = nmemb * size;
	i = 0;
	alloc = malloc(count);
	if (alloc == 0)
		return (0);
	while (i < count)
	{
		alloc[i] = 0;
		i++;
	}
	return (alloc);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	if (n == 0 || str1 == NULL || str2 == NULL)
		return (0);
	while (*str1 == *str2 && (*str1 != '\0') && i < n)
	{
		i++;
		if (i != n)
		{
			str1++;
			str2++;
		}
	}
	return (*str1 - *str2);
}