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

int		max_width_field_dixu(t_arg *arg)
{
	int max;

	if (ft_strlen(arg->value) > arg->precision &&
			ft_strlen(arg->value) > arg->mfw)
		max = ft_strlen(arg->value);
	else if (arg->mfw > arg->precision)
		max = arg->mfw;
	else
		max = arg->precision;
	if (arg->value[0] == '-' && arg->precision > ft_strlen(arg->value) - 1)
		max = max + 1;
	return (max);
}

char	*you_are_zero_dixu(t_arg *arg, char *res, t_res a)
{
	int len;
	int i;

	len = ft_strlen(arg->value);
	i = 0;
	if (!arg->mfw && !arg->point)
		res[0] = '0';
	else if (arg->minus && ((arg->mfw && !arg->point) || arg->precision))
	{
		a = minus_0_space_dixu(arg, a, len);
		res = if_minus_dixu(arg, res, a);
	}
	else if (!arg->minus && ((arg->mfw && !arg->point) ||
		(arg->zero && arg->precision) || (arg->point && arg->precision)))
	{
		a = no_minus_0_space_dixu(arg, a, len);
		res = if_no_minus_dixu(arg, res, a);
	}
	else
		you_are_zero_dixu2(arg, res);
	return (res);
}

char	*create_and_fill_di(t_arg *arg)
{
	int		max;
	char	*res;
	t_res	a;

	ft_bzero(&a, sizeof(a));
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

char	*if_minus_dixu(t_arg *arg, char *res, t_res a)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (a.minus)
	{
		res[i++] = '-';
		j++;
	}
	while (a.nb_zero--)
		res[i++] = '0';
	while (arg->value[j])
		res[i++] = arg->value[j++];
	while (a.nb_space--)
		res[i++] = ' ';
	res[i] = '\0';
	return (res);
}

char	*if_no_minus_dixu(t_arg *arg, char *res, t_res a)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (a.nb_space--)
		res[i++] = ' ';
	if (a.minus)
	{
		res[i++] = '-';
		j++;
	}
	while (a.nb_zero--)
		res[i++] = '0';
	while (arg->value[j])
		res[i++] = arg->value[j++];
	res[i] = '\0';
	return (res);
}
