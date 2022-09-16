/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:00:28 by lmelard           #+#    #+#             */
/*   Updated: 2021/12/16 10:20:59 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	ft_plusmin(char c)
{
	if (c == '-')
		return (1);
	else if (c == '+')
		return (2);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	nb;	

	n = 1;
	nb = 0;
	while (*str && ft_isspace(*str) == 1)
		str++;
	if (ft_plusmin(*str) == 1)
	{
		n = n * -1;
		str++;
	}
	else if (ft_plusmin(*str) == 2)
		str++;
	while (*str && ft_isdigit(*str) == 1)
	{
		nb = nb * 10 + *str - 48;
		str++;
	}
	nb = nb * n;
	return (nb);
}
