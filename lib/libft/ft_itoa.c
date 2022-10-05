/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <lmelard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:15:07 by lmelard           #+#    #+#             */
/*   Updated: 2022/10/05 16:01:13 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static size_t	ft_count(long long int n)
{
	int						c;
	unsigned long long int	nb;

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

static unsigned long long int	ft_define_nb(long long int n)
{
	unsigned long long int	nb;

	nb = 0;
	if (n >= 0)
		nb = n;
	else if (n < 0)
		nb = -n;
	return (nb);
}

char	*ft_itoa(long long int n)
{
	char					*str;
	int						len;
	unsigned long long int	nb;

	nb = 0;
	str = (char *)malloc(sizeof(char) * (ft_count(n) + 1));
	if (!str)
		return (NULL);
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
