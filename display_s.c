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

int		max_width_field_s(t_arg *arg)
{
	int max;

	max = 0;
	ft_strlen(arg->value);
	if (arg->mfw && arg->precision)
	{
		if (arg->mfw >= ft_strlen(arg->value))
			max = arg->mfw;
		else if (arg->precision >= ft_strlen(arg->value))
			max = ft_strlen(arg->value);
		else
			max = arg->mfw;
	}
	else if (!arg->precision && arg->mfw)
	{
		if (ft_strlen(arg->value) >= arg->mfw)
			max = ft_strlen(arg->value);
		else
			max = arg->mfw;
	}
	else if (!arg->mfw && arg->precision)
		max = arg->precision;
	return (max);
}

t_res	get_space_s(t_arg *arg, t_res a)
{
	int	len;
	int	mfw;
	int	precision;

	mfw = arg->mfw;
	precision = arg->precision;
	len = ft_strlen(arg->value);
	if (!arg->point && mfw > len)
		a.nb_space = mfw - len;
	if (arg->point)
	{
		if (!precision)
			a.nb_space = mfw;
		else if (precision > len && mfw > len)
			a.nb_space = mfw - len;
		else if (mfw >= precision  &&
	((precision <= len && mfw > len) || (mfw && precision < len && mfw <= len)))
			a.nb_space = mfw - precision;
	}
	return (a);
}

char	*if_minus_s(t_arg *arg, char *res, t_res a)
{
	int i;
	int j;
	int precision;

	i = 0;
	j = 0;
	precision = arg->precision;
	if (arg->point)
	{
		while (precision-- && arg->value[j])
			res[i++] = arg->value[j++];
	}
	else
	{
		while (arg->value[j])
			res[i++] = arg->value[j++];
	}
	while (a.nb_space--)
		res[i++] = ' ';
	res[i] = '\0';
	return (res);
}

char	*if_no_minus_s(t_arg *arg, char *res, t_res a)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (a.nb_space--)
	{
		if (!arg->zero)
			res[i++] = ' ';
		else
			res[i++] = '0';
	}
	if (arg->point)
	{
		while (arg->precision-- && arg->value[j])
			res[i++] = arg->value[j++];
	}
	else
	{
		while (arg->value[j])
			res[i++] = arg->value[j++];
	}
	res[i] = '\0';
	return (res);
}

char	*create_and_fill_s(t_arg *arg)
{
	int		max;
	t_res	a;
	char	*res;

	ft_bzero(&a, sizeof(a));
	if (arg->precision < 0 && !arg->mfw)
		arg->precision = -arg->precision;
	else if (arg->precision < 0 && arg->mfw)
		arg->precision = 0;
	max = max_width_field_s(arg);
	if (!arg->value)
		arg->value = "(null)";
	a = get_space_s(arg, a);
	if (!(res = (char *)malloc(sizeof(char) * (max + 1))))
		return (0);
	res[max] = '\0';
	if (arg->minus)
		res = if_minus_s(arg, res, a);
	else if (!arg->minus)
		res = if_no_minus_s(arg, res, a);
	return (res);
}
