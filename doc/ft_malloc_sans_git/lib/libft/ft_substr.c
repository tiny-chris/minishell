/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:22:14 by lmelard           #+#    #+#             */
/*   Updated: 2021/12/16 10:27:01 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			l;

	if (!s)
		return (NULL);
	l = ft_strlen(&s[start]);
	if (len < l)
		l = len;
	str = ft_calloc(sizeof(char), (l + 1));
	if (!str)
		return (NULL);
	if (start >= ft_strlen(s))
		return (str);
	else
		ft_strlcpy(str, &s[start], (l + 1));
	return (str);
}
