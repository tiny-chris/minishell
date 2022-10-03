/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 01:55:55 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/03 18:59:27 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TEST CHRIS

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

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
		new_str = ft_malloc(data, (char *)new_str, TAB_STR1, (str_len - start));
	else
		// new_str = malloc(sizeof(char) * (len + 1));
		new_str = ft_malloc(data, new_str, TAB_STR1, (len + 1));
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
	str = ft_malloc(data, str, TAB_STR1, (s1len + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	return (str);
}

/*	SPLIT avec ft_malloc
*/
// static size_t	ft_wordcount(const char *s, char c)
// {
// 	size_t	w;
// 	size_t	i;

// 	w = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		while (s[i] && s[i] == c)
// 			i++;
// 		if (s[i] != c && s[i] != '\0')
// 		{
// 			w++;
// 			while (s[i] && s[i] != c)
// 				i++;
// 		}
// 	}
// 	return (w);
// }

// static char	*ft_malloc_str(const char *s, char c)
// {
// 	char		*str;
// 	size_t		i;

// 	i = 0;
// 	while (s[i] && (s[i] != c))
// 		i++;
// 	str = (char *)malloc(sizeof(char) * (i + 1));
// 	if (!str)
// 		return (NULL);
// 	str[i] = '\0';
// 	i--;
// 	while (i > 0)
// 	{
// 		str[i] = s[i];
// 		i--;
// 	}
// 	str[i] = s[i];
// 	return (str);
// }

// static void	*ft_free(char **str, size_t i)
// {
// 	size_t	j;

// 	j = 0;
// 	while (j < i)
// 	{
// 		free(str[j]);
// 		j++;
// 	}
// 	free(str);
// 	return (NULL);
// }

// char	**ft_split(void *data, char const *s, char c)
// {
// 	char	**str;
// 	size_t	i;
// 	size_t	j;

// 	str = ft_malloc(data, str, TAB_STRS, (ft_wordcount(s, c) + 1));
// 	if (!str)
// 		return (NULL);
// 	j = (ft_wordcount(s, c) + 1);
// 	i = 0;
// 	while (*s && i < j)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if (*s != c && *s != '\0')
// 		{
// 			str[i] = ft_malloc_str(s, c);
// 			if (!str[i])
// 				return (ft_free(str, i));
// 			while (*s && *s != c)
// 				s++;
// 			i++;
// 		}
// 	}
// 	return (str[i] = 0, str);
// }
