/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:32:35 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/06/06 14:23:19 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*fall(char **src);
static char	**splitter(char **dest, char const *s, char c, int size);
static int	count(char const *str, char c);

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**dest;

	size = count(s, c);
	dest = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dest)
	{
		fall(dest);
		return (NULL);
	}
	dest = splitter(dest, s, c, size);
	return (dest);
}

static	char	**splitter(char **dest, char const *s, char c, int size)
{
	int	len;
	int	i;
	int	j;
	int	a;

	i = 0;
	a = 0;
	while (i < size)
	{
		len = 0;
		j = 0;
		while (s[a] == c)
			a++;
		while (s[a + len] && s[a + len] != c)
			len++;
		dest[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!dest[i])
			return (fall(dest));
		while (j < len)
			dest[i][j++] = s[a++];
		dest[i++][j] = '\0';
	}
	dest[i] = NULL;
	return (dest);
}

static int	count(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static void	*fall(char **src)
{
	int	i;

	i = 0;
	while (src[i])
		free(src[i++]);
	free(src);
	return (NULL);
}
