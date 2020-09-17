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

char	*ft_convert_base_x(t_arg *arg)
{
	unsigned int	nb;
	char			*tmp;

	tmp = arg->value;
	nb = (unsigned int)ft_atoi_base_xu(arg->value, "0123456789");
	arg->value = ft_itoa_base_xu(nb, "0123456789abcdef");
	free(tmp);
	return (arg->value);
}

char	*fill_up_field_x(t_arg *arg, char *res, t_res a)
{
	if (arg->minus)
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

char	*create_and_fill_x(t_arg *arg)
{
	int		max;
	char	*res;
	t_res	a;

	ft_bzero(&a, sizeof(a));
	arg->value = ft_convert_base_x(arg);
	max = max_width_field_dixu(arg);
	if (!(res = (char *)malloc(sizeof(char) * (max + 1))))
		return (0);
	res[max] = '\0';
	if (arg->value[0] == '0')
		res = you_are_zero_dixu(arg, res, a);
	else
		res = fill_up_field_x(arg, res, a);
	return (res);
}

char	*create_and_fill_bigx(t_arg *arg)
{
	char	*res;
	int		i;

	res = create_and_fill_x(arg);
	i = 0;
	while (res[i])
	{
		if (res[i] >= 'a' && res[i] <= 'z')
			res[i] = res[i] - 32;
		i++;
	}
	return (res);
}
