/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaillag <cgaillag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:35:15 by lmelard           #+#    #+#             */
/*   Updated: 2022/09/28 01:31:06 by cgaillag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1len;
	size_t	s2len;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, (s1len + 1));
	ft_strlcat(str, s2, (s1len + s2len + 1));
	return (str);
}
