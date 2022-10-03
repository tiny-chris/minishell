/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmelard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:15:07 by lmelard           #+#    #+#             */
/*   Updated: 2021/12/10 16:29:23 by lmelard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	nb;

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
