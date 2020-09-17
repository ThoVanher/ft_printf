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

int		place_in_base_x(char *base, char c)
{
	int i;

	i = 0;
	while (c != base[i])
		i++;
	return (i);
}

long	ft_atoi_base_xu(char *str, char *base)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 0;
	res = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n' || str[i] ==
'\r' || str[i] == '\v' || str[i] == ' ' || str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign++;
		i++;
	}
	while (str[i])
	{
		res = res * ft_strlen(base) + place_in_base_x(base, str[i]);
		i++;
	}
	if (sign % 2 == 1)
		res = -res;
	return (res);
}

int		nb_digit_x(long nbr, char *base_to)
{
	int len;
	int res;

	len = ft_strlen(base_to);
	res = 1;
	while (nbr / len != 0)
	{
		nbr = nbr / len;
		res++;
	}
	return (res);
}

char	*convert_x(long nbr, int begin, char *res, char *base_to)
{
	int tmp;
	int len;
	int digit;

	len = ft_strlen(base_to);
	digit = nb_digit_x(nbr, base_to);
	if (begin == 1)
		digit++;
	tmp = digit;
	while (digit > 0)
	{
		res[digit - 1] = base_to[nbr % len];
		nbr = nbr / len;
		digit--;
	}
	if (begin == 1)
		res[0] = '-';
	res[tmp] = '\0';
	return (res);
}

char	*ft_itoa_base_xu(long nbr, char *base_to)
{
	char	*res;
	int		digit;
	int		begin;

	digit = nb_digit_x(nbr, base_to);
	begin = 0;
	if (!(res = (char *)malloc((digit + 1) * sizeof(char))))
		return (0);
	if (nbr < 0)
	{
		begin++;
		nbr = -nbr;
	}
	convert_x(nbr, begin, res, base_to);
	return (res);
}
