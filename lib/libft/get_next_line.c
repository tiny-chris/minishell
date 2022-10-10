/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:49:40 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/10 16:33:36 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_check_n(char *s1)
{
	size_t	i;

	i = 0;
	if (s1 == NULL)
		return (0);
	while (s1[i] != '\0' && s1[i] != '\n')
		i++;
	if (s1[i] == '\0')
		return (0);
	else
		return (i + 1);
}

char	*ft_get_line(char *s1)
{
	size_t		i;
	char		*str;

	i = 0;
	if (ft_check_n(s1) != 0)
		str = malloc(sizeof(char) * (ft_check_n(s1) + 1));
	else
		str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\n' && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	if (ft_check_n(s1) != 0)
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_get_buffer(char *tmp)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!tmp)
		return (NULL);
	i = ft_check_n(tmp);
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen_gnl(tmp) - i + 1));
	if (!str)
		return (NULL);
	while (tmp[i] != '\0')
	{
		str[j] = tmp[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free(tmp);
	if (str[0] == '\0')
	{
		free(str);
		str = NULL;
	}
	return (str);
}

char	*ft_find_line(char **tmp, char **line)
{
	*line = ft_get_line(*tmp);
	if (ft_check_n(*tmp) == 0)
	{
		free(*tmp);
		*tmp = NULL;
	}
	else
		*tmp = ft_get_buffer(*tmp);
	return (*line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE +1];
	static char	*tmp;
	char		*line;
	int			nbyte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nbyte = 1;
	while (nbyte > 0 && ft_check_n(tmp) == 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		nbyte = read(fd, buffer, BUFFER_SIZE);
		if (nbyte < 0)
			return (NULL);
		if (nbyte > 0)
			tmp = ft_strjoin_gnl(tmp, buffer);
	}
	if (tmp == NULL)
		return (NULL);
	return (ft_find_line(&tmp, &line));
}
