/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:52:30 by athirion          #+#    #+#             */
/*   Updated: 2022/06/30 12:36:55 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_w_dup2(t_data *data, int fd, int std)
{
	if (dup2(fd, std) == -1)
		ft_exitmsg(data, "dup2");
}

void	*ft_w_malloc(t_data *data, size_t size)
{
	void	*mem;

	(void)data;
	mem = NULL;
	mem = malloc (size);
	if (!mem)
		ft_exitmsg (data, "malloc");
	return (mem);
}

char	*ft_w_getcwd(t_data *data)
{
	char	*cwd;

	(void)data;
	cwd = NULL;
	cwd = getcwd (NULL, PATH_MAX);
	if (!cwd)
		ft_exitmsg (data, "getcwd malloc");
	return (cwd);
}

char	*ft_w_substr(t_data *data, char const *s, size_t start, size_t len)
{
	char	*str;

	(void)data;
	str = ft_substr (s, (unsigned int) start, len);
	if (!str)
		ft_exitmsg (data, "substr malloc");
	return (str);
}

char	*ft_w_strdup(t_data *data, const char *s1)
{
	char	*str;

	(void)data;
	str = ft_strdup (s1);
	if (!str)
		ft_exitmsg (data, "strdup malloc");
	return (str);
}
