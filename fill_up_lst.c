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

int		stars_with_point(const char *str, t_arg *arg, int i, int tmp)
{
	while (str[i] != '%')
	{
		if (str[i] == '*')
			arg->mfw_star = -1;
		i--;
	}
	i = tmp;
	while (!is_convert(str[i]))
	{
		if (str[i] == '*')
			arg->precision_star = -1;
		i++;
	}
	return (i);
}

int		stars_without_point(const char *str, t_arg *arg, int i)
{
	i++;
	while (!is_convert(str[i]))
	{
		if (str[i] == '*')
			arg->mfw_star = -1;
		i++;
	}
	return (i);
}

void	finish_to_fill_lst(const char *str, t_arg **begin)
{
	int		i;
	t_arg	*arg;

	i = 0;
	arg = *begin;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			if (check_valid_arg(str, i))
			{
				get_mfw_precision(str, arg, i);
				arg = arg->next;
			}
			while (str[i] && !is_convert(str[i]))
				i++;
			i++;
		}
		else
			i++;
	}
}

void	convert_mfw_precision(const char *str, t_arg *arg, int i, int j)
{
	if (j == 1)
	{
		while (ft_isdigit(str[i]))
		{
			arg->mfw = 10 * arg->mfw + (str[i] - 48);
			i++;
		}
	}
	if (j == 2)
	{
		while (ft_isdigit(str[i]))
		{
			arg->precision = 10 * arg->precision + (str[i] - 48);
			i++;
		}
	}
}

void	get_type_and_stars(const char *str, int *i, t_arg **begin)
{
	t_arg	*arg;
	int		tmp;

	arg = ft_lstlast_a(*begin);
	while (!is_convert(str[*i]))
		(*i)++;
	(*i)--;
	while (str[*i] != '%' && str[*i] != '.')
		(*i)--;
	tmp = *i;
	if (str[*i] == '.')
		*i = stars_with_point(str, arg, *i, tmp);
	else if (str[*i] == '%')
		*i = stars_without_point(str, arg, *i);
	arg->type = str[*i];
	(*i)++;
}
