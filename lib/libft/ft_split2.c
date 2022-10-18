/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:36:42 by cgaillag          #+#    #+#             */
/*   Updated: 2022/10/18 17:45:21 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	******** FT_SPLIT ********
**	**************************
**	Function that splits a string into a table of strings by using a defined 
**	separator (char).
**
**	Actions:
**	- calculate the number of future strings (words)
**	- malloc the char ** (table of strings) with number of words + 1
**	- in a loop, get the size of each word and fill words with correct content
**	- plan a free function if allocation is not possible
**	- add a NULL string at the end
**	**************************
**
** Static - Counts the number of words in the string when using separator 'c' 
*/
static int	ft_count_word(char const *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str && str[i])
	{
		if (str[i] != c)
		{
			word++;
			while (str[i] != c && str[i])
				i++;
		}
		while (str[i] && str[i] == c)
			i++;
	}
	return (word);
}

/*	Static - Gets the size of each word (1 by 1)
*/
static int	ft_size_word(char const *str, char c, int i)
{
	int	size;

	size = 0;
	while (str[i] && str[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

/*	Static - Frees words + char** if malloc problem
*/
static void	ft_free_split(char **tab, int j)
{
	while (j-- > 0)
		free(tab[j]);
	free(tab);
}

/* Main function 
*/
char	**ft_split2(char const *str, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		word;
	int		size;

	i = 0;
	j = -1;
	word = ft_count_word(str, c);
	tab = (char **) malloc(sizeof(char *) * (word + 1));
	if (tab == NULL)
		return (NULL);
	while (++j < word)
	{
		while (str[i] == c)
			i++;
		size = ft_size_word(str, c, i);
		tab[j] = ft_substr(str, i, size);
		if (!tab[j])
			return (ft_free_split(tab, j), NULL);
		i += size;
	}
	tab[j] = 0;
	return (tab);
}
