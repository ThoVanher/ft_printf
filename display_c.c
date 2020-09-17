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

int		max_width_field_c(t_arg *arg)
{
	int value;
	int max;

	value = ft_atoi(arg->value);
	if (value == 0 && arg->mfw < 2)
		max = 2;
	else if (value == 0 && arg->mfw > 1)
		max = 1 + arg->mfw;
	else if (!arg->mfw)
		max = 1;
	else
		max = arg->mfw;
	return (max);
}

char	conv_int_to_char(t_arg *arg)
{
	int		value_tmp;
	char	value;

	value_tmp = ft_atoi(arg->value);
	value = (char)value_tmp;
	return (value);
}

char	*if_minus_c(t_arg *arg, char *res, char c)
{
	int nb_space;
	int i;

	nb_space = 0;
	i = 0;
	if (arg->mfw > 1)
		nb_space = arg->mfw - 1;
	if (c == 0)
	{
		res[0] = '\0';
		return (res);
	}
	else
		res[i++] = c;
	while (nb_space--)
		res[i++] = ' ';
	return (res);
}

char	*if_no_minus_c(t_arg *arg, char *res, char c)
{
	int nb_space;
	int i;

	nb_space = 0;
	i = 0;
	if (arg->mfw > 1)
		nb_space = arg->mfw - 1;
	while (nb_space--)
	{
		if (!arg->zero)
			res[i++] = ' ';
		else
			res[i++] = '0';
	}
	res[i++] = c;
	return (res);
}

char	*create_and_fill_c(t_arg *arg)
{
	int		max;
	char	*res;
	char	c;
	int		value;

	value = ft_atoi(arg->value);
	max = max_width_field_c(arg);
	c = 0;
	if (!(res = (char *)malloc(sizeof(char) * (max + 1))))
		return (0);
	res[max] = '\0';
	if (arg->minus)
	{
		if (value != 0)
			c = conv_int_to_char(arg);
		res = if_minus_c(arg, res, c);
	}
	else
	{
		if (value != 0)
			c = conv_int_to_char(arg);
		res = if_no_minus_c(arg, res, c);
	}
	return (res);
}
