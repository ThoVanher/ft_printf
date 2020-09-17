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

int		max_width_field_ptr(t_arg *arg, int len)
{
	int max;

	if (arg->mfw && arg->mfw > len)
		max = arg->mfw;
	else
		max = len;
	return (max);
}

char	*if_minus_ptr(char *res, char *str, int max)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (res[i])
		str[j++] = res[i++];
	while (j < max)
		str[j++] = ' ';
	return (str);
}

char	*if_no_minus_ptr(t_arg *arg, char *res, char *str, int max)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(res);
	if (!arg->zero)
	{
		while (j < max - len)
			str[j++] = ' ';
		while (res[i])
			str[j++] = res[i++];
	}
	else
	{
		str[0] = '0';
		str[1] = 'x';
		while (j < max - len)
			str[j++ + 2] = '0';
		while (res[i + 2])
			str[j++ + 2] = res[i++ + 2];
	}
	return (str);
}

char	*fill_up_field_ptr(t_arg *arg, char *res, int len)
{
	int		i;
	int		j;
	int		max;
	char	*str;

	i = 0;
	j = 0;
	max = max_width_field_ptr(arg, len);
	if (!(str = (char *)malloc(sizeof(char) * (max + 1))))
		return (0);
	if (arg->minus)
		if_minus_ptr(res, str, max);
	if (!arg->minus)
		if_no_minus_ptr(arg, res, str, max);
	str[max] = '\0';
	return (str);
}

char	*create_and_fill_ptr(t_arg *arg)
{
	char	*res;
	char	*base;
	int		digit;
	char	*tmp;

	base = "0123456789abcdef";
	if (!(arg->pointeur == 0 && arg->point))
	{
		digit = nb_digit_ptr(arg->pointeur, base);
		if (!(res = (char *)malloc((digit + 1) * sizeof(char))))
			return (0);
		convert_ptr(arg->pointeur, res, base);
		tmp = res;
		res = ft_strjoin("0x", res);
		free(tmp);
		tmp = res;
		res = fill_up_field_ptr(arg, res, ft_strlen(res));
		free(tmp);
	}
	else
	{
		res = "0x";
		res = fill_up_field_ptr(arg, res, 2);
	}
	return (res);
}
