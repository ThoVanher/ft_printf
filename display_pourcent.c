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

void	if_no_minus_pourcent(t_arg *arg, char *res, int max)
{
	int i;

	i = 0;
	if (arg->zero && arg->mfw)
	{
		while (i < max - 1)
			res[i++] = '0';
	}
	else
	{
		while (i < max - 1)
			res[i++] = ' ';
	}
	res[i] = '%';
}

char	*fill_up_field_pourcent(t_arg *arg, char *res, int max)
{
	int i;

	if (arg->minus)
	{
		res[0] = '%';
		i = 1;
		while (i < max)
			res[i++] = ' ';
	}
	if (!arg->minus)
		if_no_minus_pourcent(arg, res, max);
	res[max] = '\0';
	return (res);
}

int		is_convert(char c)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X' ||
			c == '%' || c == 's' || c == 'c' || c == 'p')
		return (1);
	return (0);
}

int		is_flag(char c)
{
	if (c == '-' || c == '0' || c == '.' || c == '*')
		return (1);
	return (0);
}

char	*create_and_fill_pourcent(t_arg *arg)
{
	char	*res;
	int		max;

	if (arg->mfw)
		max = arg->mfw;
	else
		max = 1;
	if (!(res = (char *)malloc(sizeof(char) * (max + 1))))
		return (0);
	fill_up_field_pourcent(arg, res, max);
	return (res);
}
