#include "includes/philo.h"

size_t		ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

void		ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*memory;

	i = 0;
	memory = s;
	while (i < n)
	{
		memory[i] = 0;
		i++;
	}
}

char					*ft_strdup(const char *s1)
{
	char				*str;
	int					i;
	const int			max_len = ft_strlen(s1);

	i = 0;
	str = malloc(max_len + 1);
	if (!str)
		return (NULL);
	while (i < max_len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

int	ft_atoi(const char *str)
{
	int	i;
	int				result;
	char			c;

	if (!str)
		return (ATOI_ERROR);
	i = 0;
	if (*str == '+')
		++str;
	result = 0;
	c = str[i];
	while (c >= '0' && c <= '9')
	{
		result = result * 10 + c - '0';
		c = str[++i];
	}
	if (str[i] || i == 0)
		return (ATOI_ERROR);
	return (result);
}

void	*ft_malloc(size_t size)
{
	size_t	i;
	char	*ret;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = '\0';
		i++;
	}
	return ((void *)ret);
}
