#include <stdio.h>
#include "libft/libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s;

	i = 0;
	s = ft_strlen(src);
	if (size == 0)
		return (s);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	max;
	size_t	olen;
	char	*dest;

	if (!s)
		return (NULL);
	olen = ft_strlen((char *)s);
	if (start >= olen)
	{
		dest = malloc(1);
		if (dest)
			dest[0] = '\0';
		return (dest);
	}
	max = olen - start;
	if (len > max)
		len = max;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[start], len + 1);
	return (dest);
}

double	ft_atof(char *str)
{
	int		dot;
	int		neg;
	double	res1;
	char	*s1;
	char	*s2;

	dot = 0;
	while (str[dot] && str[dot] != '.')
		dot++;
	if (dot == (int)ft_strlen(str))
		return (ft_atoi(str));
	neg = 1;
	if (str[0] == '-')
	{
		s1 = ft_substr(str, 1, dot - 1);
		neg = -1;
	}
	else
		s1 = ft_substr(str, 0, dot);
	s2 = ft_substr(str, dot + 1, (ft_strlen(str) - dot));
	res1 = ft_atoi(s2);
	while (ft_strlen(str) - (++dot))
		res1 /= 10;
	return ((double)(ft_atoi(s1) * neg) + (double)(res1 * neg));
}

int	main(int ac, char **av)
{
	double res;

	(void)ac;
	res = ft_atof(av[1]);
	printf("res: %f\n", res);
	return (0);
}