/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:11:59 by cvidon            #+#    #+#             */
/*   Updated: 2022/01/28 18:42:13 by clem9nt          888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Read and parse the input
 */

static int	ft_read(int (*options[8])(va_list), const char *fmt, va_list args)
{
	int	ret;
	int	id;

	ret = 0;
	while (*fmt)
	{
		if (*fmt != '%')
			ret += (int)write(1, fmt++, 1);
		else
		{
			fmt++;
			id = 0 * (*fmt == '%')
				+ 1 * (*fmt == 'c')
				+ 2 * (*fmt == 's')
				+ 3 * ((*fmt == 'i') | (*fmt == 'd'))
				+ 4 * (*fmt == 'u')
				+ 5 * (*fmt == 'x')
				+ 6 * (*fmt == 'X')
				+ 7 * (*fmt == 'p')
				;
			ret += options[id](args);
			fmt++;
		}
	}
	return (ret);
}

/*
 * Initialize the supported flags
 */

int	ft_printf(const char *fmt, ...)
{
	int		(*options[8])(va_list);
	va_list	args;
	int		ret;

	options[0] = ft_pct;
	options[1] = ft_chr;
	options[2] = ft_str;
	options[3] = ft_nbr;
	options[4] = ft_uns;
	options[5] = ft_hx1;
	options[6] = ft_hx2;
	options[7] = ft_ptr;
	va_start(args, fmt);
	ret = ft_read(options, fmt, args);
	va_end(args);
	return (ret);
}
