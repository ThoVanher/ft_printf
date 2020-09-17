/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thvanher <thvanher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 10:50:01 by thvanher          #+#    #+#             */
/*   Updated: 2020/08/11 10:50:22 by thvanher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void				ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

static int			nb_digit(int nbr)
{
	int res;

	res = 1;
	if (nbr < 0)
		res++;
	while (nbr / 10 != 0)
	{
		nbr = nbr / 10;
		res++;
	}
	return (res);
}

static unsigned int	is_neg(int nbr)
{
	unsigned int nombre;

	if (nbr < 0)
		nombre = -nbr;
	else
		nombre = nbr;
	return (nombre);
}

char				*ft_itoa(int nbr)
{
	unsigned int	nombre;
	char			*res;
	int				i;
	int				digit;
	int				j;

	i = 0;
	digit = nb_digit(nbr);
	j = 0;
	nombre = is_neg(nbr);
	if (!(res = (char *)malloc((digit + 1) * sizeof(char))))
		return (0);
	if (nbr < 0)
	{
		res[0] = '-';
		j = 1;
	}
	while (digit - 1 - i >= j)
	{
		res[digit - 1 - i] = nombre % 10 + '0';
		nombre = nombre / 10;
		i++;
	}
	res[digit] = '\0';
	return (res);
}
