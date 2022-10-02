/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:11:59 by cvidon            #+#    #+#             */
/*   Updated: 2022/01/28 18:42:37 by clem9nt          888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_uns(va_list args)
{
	unsigned int	nb;
	int				ret;

	ret = 0;
	nb = va_arg(args, unsigned int);
	ft_putnbr_base(nb, 10, "0123456789", &ret);
	return (ret);
}

int	ft_hx1(va_list args)
{
	unsigned int	nb;
	int				ret;

	ret = 0;
	nb = va_arg(args, unsigned int);
	ft_putnbr_base(nb, 16, "0123456789abcdef", &ret);
	return (ret);
}

int	ft_hx2(va_list args)
{
	unsigned int	nb;
	int				ret;

	ret = 0;
	nb = va_arg(args, unsigned int);
	ft_putnbr_base(nb, 16, "0123456789ABCDEF", &ret);
	return (ret);
}

int	ft_ptr(va_list args)
{
	int				ret;
	unsigned long	nb;

	ret = (int)write(1, "0x", 2);
	nb = va_arg(args, unsigned long);
	ft_putnbr_base_ptr(nb, 16, "0123456789abcdef", &ret);
	return (ret);
}
