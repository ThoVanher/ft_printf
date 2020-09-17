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

t_arg	*int_to_unsigned(t_arg *arg)
{
	unsigned int	nb;
	char			*tmp;

	tmp = arg->value;
	nb = (unsigned int)ft_atoi_base_xu(arg->value, "0123456789");
	arg->value = ft_itoa_base_xu(nb, "0123456789");
	free(tmp);
	return (arg);
}

t_res	minus_0_space_dixu(t_arg *arg, t_res a, int len)
{
	int precision;
	int mfw;

	precision = arg->precision;
	mfw = arg->mfw;
	len = ft_strlen(arg->value);
	if (arg->value[0] == '-')
		a.minus = 1;
	if (a.minus && precision > len - 1)
	{
		a.nb_zero = precision - (len - 1);
		if (mfw > precision)
			a.nb_space = mfw - precision - 1;
	}
	else if (!a.minus && precision > len)
	{
		a.nb_zero = precision - len;
		if (mfw > precision)
			a.nb_space = mfw - precision;
	}
	else if (mfw > precision && mfw > len)
		a.nb_space = mfw - len;
	return (a);
}

t_res	no_minus_0_space_dixu(t_arg *arg, t_res a, int len)
{
	if (arg->value[0] == '-')
		a.minus = 1;
	if (!arg->precision && arg->mfw > len &&
	((arg->zero && arg->point) || (!arg->point && !arg->zero)))
		a.nb_space = arg->mfw - len;
	if (arg->mfw >= len && ((arg->zero && !arg->point && arg->mfw > len)
				|| (arg->precision < 0 && arg->mfw)))
		a.nb_zero = arg->mfw - len;
	else if (a.minus && arg->precision > len - 1)
	{
		a.nb_zero = arg->precision - (len - 1);
		if (arg->mfw > arg->precision)
			a.nb_space = arg->mfw - arg->precision - 1;
	}
	else if (!a.minus && arg->precision > len)
	{
		a.nb_zero = arg->precision - len;
		if (arg->mfw > arg->precision)
			a.nb_space = arg->mfw - arg->precision;
	}
	else if (arg->mfw > arg->precision && arg->mfw > len)
		a.nb_space = arg->mfw - len;
	if (arg->precision < 0 && arg->mfw)
		a.nb_space = 0;
	return (a);
}

char	*create_and_fill_u(t_arg *arg)
{
	int		max;
	char	*res;
	t_res	a;

	ft_bzero(&a, sizeof(a));
	arg = int_to_unsigned(arg);
	max = max_width_field_dixu(arg);
	if (!(res = (char *)malloc(sizeof(char) * (max + 1))))
		return (0);
	res[max] = '\0';
	if (arg->value[0] == '0')
		res = you_are_zero_dixu(arg, res, a);
	else if (arg->minus)
	{
		a = minus_0_space_dixu(arg, a, ft_strlen(arg->value));
		res = if_minus_dixu(arg, res, a);
	}
	else if (!arg->minus)
	{
		a = no_minus_0_space_dixu(arg, a, ft_strlen(arg->value));
		res = if_no_minus_dixu(arg, res, a);
	}
	return (res);
}
