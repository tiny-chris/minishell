/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 02:59:33 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/02 04:19:51 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TEST CHRIS

/*	Fonctions identifiées de la libft contenant des mallocs:
	- ft_strdup
	- ft_itoa
	- ft_split
	- ft_strjoin
	- ft_calloc (dans ft_substr)

	ft_substr utilise calloc
	==> j'ai modifié ft_substr directement

	à voir : getcwd --> juste nettoyage mais pas malloc souci
*/

/*	SUBSTR avec ft_malloc
*/
char	*ft_substr_malloc(void *data, const char *str, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	str_len;
	char	*new_str;

	new_str = NULL;
	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	if ((size_t)start >= str_len)
		return (ft_strdup(""));
	if (len + start > str_len)
		// new_str = malloc(sizeof(char) * (str_len - start));
		new_str = ft_malloc(data, TAB_STR1, (str_len - start));
	else
		// new_str = malloc(sizeof(char) * (len + 1));
		new_str = ft_malloc(data, TAB_STR1, (len + 1));
	// if (!new_str)
	// 	return (NULL);
	i = start;
	j = 0;
	while (i < str_len && j < len)
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	return (new_str);
}

/*	STRDUP avec ft_malloc
*/
static char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char	*ft_strdup_malloc(void *data, const char *s1)
{
	char	*str;
	int		s1len;

	str = NULL;
	s1len = ft_strlen(s1);
	// str = malloc(sizeof(char) * (s1len + 1));
	str = ft_malloc(data, TAB_STR1, (s1len + 1));
	// if (!str)
	// 	return (NULL);
	ft_strcpy(str, s1);
	return (str);
}

/*	ITOA avec ft_malloc
*/
static size_t	ft_count(int n)
{
	int				c;
	unsigned int	nb;

	c = 1;
	nb = 0;
	if (n < 0)
	{
		nb = -n;
		c++;
		while (nb > 9)
		{
			c++;
			nb = nb / 10;
		}
	}
	else if (n >= 0)
	{
		while (n > 9)
		{
			c++;
			n = n / 10;
		}
	}
	return (c);
}

static unsigned int	ft_define_nb(int n)
{
	unsigned int	nb;

	nb = 0;
	if (n >= 0)
		nb = n;
	else if (n < 0)
		nb = -n;
	return (nb);
}

char	*ft_itoa_malloc(void *data, int n)
{
	char			*str;
	int				len;
	unsigned int	nb;

	nb = 0;
	// str = (char *)malloc(sizeof(char) * (ft_count(n) + 1));
	str = ft_malloc(data, TAB_STR1, (ft_count(n) + 1));
	// if (!str)
	// 	return (NULL);
	len = ft_count(n);
	nb = ft_define_nb(n);
	str[len] = '\0';
	len--;
	if (nb == 0)
		str[len] = nb + 48;
	while (nb)
	{
		str[len] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	if (n < 0)
		str[len] = '-';
	return (str);
}

/*	STRJOIN avec ft_malloc
*/
char	*ft_strjoin_malloc(void *data, char const *s1, char const *s2)
{
	char	*str;
	size_t	s1len;
	size_t	s2len;

	// if (!s1 || !s2)
	// 	return (NULL);
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = ft_malloc(data, TAB_STR1, (s1len + s2len + 1));
	// str = malloc(sizeof(char) * (s1len + s2len + 1));
	// if (!str)
	// 	return (NULL);
	ft_strlcpy(str, s1, (s1len + 1));
	ft_strlcat(str, s2, (s1len + s2len + 1));
	return (str);
}

/*	SPLIT avec ft_malloc
*/
static size_t	ft_wordcount(const char *s, char c)
{
	size_t	w;
	size_t	i;

	w = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			w++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (w);
}

static char	*ft_malloc_str(void *data, const char *s, char c)
{
	char		*str;
	size_t		i;

	i = 0;
	while (s[i] && (s[i] != c))
		i++;
	str = ft_malloc(data, TAB_STR1, (i + 1));
	// str = (char *)malloc(sizeof(char) * (i + 1));
	// if (!str)
	// 	return (NULL);
	str[i] = '\0';
	i--;
	while (i > 0)
	{
		str[i] = s[i];
		i--;
	}
	str[i] = s[i];
	return (str);
}

static void	*ft_free(char **str, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(str[j]);
		j++;
	}
	free(str);
	return (NULL);
}

char	**ft_split_malloc(void *data, char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;

	str = ft_malloc(data, TAB_STRS, (ft_wordcount(s, c) + 1));
	// str = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	// if (!str)
	// 	return (NULL);
	j = (ft_wordcount(s, c) + 1);
	i = 0;
	while (*s && i < j)
	{
		while (*s && *s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			str[i] = ft_malloc_str(data, s, c);
			// str[i] = ft_malloc_str(s, c);
			if (!str[i])
				return (ft_free(str, i));
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	return (str[i] = 0, str);
}
