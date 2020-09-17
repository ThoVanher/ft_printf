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

int		nb_digit_ptr(unsigned long long int nbr, char *base_to)
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

char	*convert_ptr(unsigned long long int nbr, char *res, char *base_to)
{
	int tmp;
	int len;
	int digit;

	len = ft_strlen(base_to);
	digit = nb_digit_ptr(nbr, base_to);
	tmp = digit;
	while (digit > 0)
	{
		res[digit - 1] = base_to[nbr % len];
		nbr = nbr / len;
		digit--;
	}
	res[tmp] = '\0';
	return (res);
}
