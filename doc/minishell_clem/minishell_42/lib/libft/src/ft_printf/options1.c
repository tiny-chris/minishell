/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options1.c                                        :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:11:59 by cvidon            #+#    #+#             */
/*   Updated: 2022/01/28 18:42:34 by clem9nt          888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pct(va_list args)
{
	(void)args;
	return ((int)write(1, "%", 1));
}

int	ft_chr(va_list args)
{
	char	c;

	c = (char) va_arg(args, int);
	return ((int)write(1, &c, 1));
}

int	ft_str(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		return ((int)write(1, "(null)", 6));
	return ((int)write(1, str, ft_strlen(str)));
}

int	ft_nbr(va_list args)
{
	int	nb;
	int	ret;

	ret = 0;
	nb = va_arg(args, int);
	ft_putnbr_base(nb, 10, "0123456789", &ret);
	return (ret);
}
