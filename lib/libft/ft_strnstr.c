/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:29:56 by lmelard           #+#    #+#             */
/*   Updated: 2021/12/14 16:02:20 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t	l;

	i = 0;
	l = len;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && (len > 0))
	{
		while (haystack[i] == needle[i] && l > 0 && haystack[i] && needle[i])
		{
			i++;
			l--;
		}
		if (needle[i] != '\0' && l == 0)
			return (0);
		if (l == 0 || needle[i] == '\0')
			return ((char *)haystack);
		haystack++;
		i = 0;
		len--;
		l = len;
	}
	return (0);
}
