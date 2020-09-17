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

void	minus_zero_point(const char *str, t_arg *arg, int i)
{
	int zero_die;

	zero_die = 0;
	while (str[i] && !is_convert(str[i]))
	{
		if ((ft_isdigit(str[i]) || str[i] == '.') && str[i] != '0')
			zero_die++;
		if (str[i] == '-')
			arg->minus++;
		if (str[i] == '0' && !zero_die)
			arg->zero = 1;
		if (arg->minus && arg->zero)
			arg->zero = 0;
		if (str[i] == '.')
			arg->point++;
		i++;
	}
}

int		mfw_if_point(const char *str, t_arg *arg, int i)
{
	int j;

	j = 0;
	while (str[i] && j != arg->point)
	{
		if (str[i] == '.')
			j++;
		i++;
	}
	i--;
	return (mfw_if_point2(str, arg, i));
}

int		mfw_if_no_point(const char *str, t_arg *arg, int i)
{
	while (!is_convert(str[i]))
		i++;
	i--;
	while (str[i] != '%')
	{
		if (ft_isdigit(str[i]))
		{
			while (ft_isdigit(str[i]))
				i--;
			convert_mfw_precision(str, arg, i + 1, 1);
			return (0);
		}
		if (str[i] == '*')
		{
			arg->mfw = arg->mfw_star;
			return (0);
		}
		i--;
	}
	return (0);
}

int		precision(const char *str, t_arg *arg, int i)
{
	int j;

	j = 0;
	while (str[i] && j != arg->point)
	{
		if (str[i] == '.')
			j++;
		i++;
	}
	while (!is_convert(str[i]))
	{
		if (str[i] == '*')
		{
			arg->precision = arg->precision_star;
			return (0);
		}
		else if (ft_isdigit(str[i]) && str[i] != '0')
		{
			convert_mfw_precision(str, arg, i, 2);
			return (0);
		}
		i++;
	}
	return (0);
}

void	get_mfw_precision(const char *str, t_arg *arg, int i)
{
	minus_zero_point(str, arg, i);
	if (arg->point)
	{
		mfw_if_point(str, arg, i);
		precision(str, arg, i);
	}
	else
		mfw_if_no_point(str, arg, i);
	if (arg->mfw < 0)
	{
		arg->minus = 1;
		arg->mfw = -arg->mfw;
	}
}
