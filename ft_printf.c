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

char	*get_arg(t_arg *arg)
{
	char *res;

	res = 0;
	if (arg->type == 'd' || arg->type == 'i')
		res = create_and_fill_di(arg);
	else if (arg->type == 'c')
		res = create_and_fill_c(arg);
	else if (arg->type == 'u')
		res = create_and_fill_u(arg);
	else if (arg->type == 'x')
		res = create_and_fill_x(arg);
	else if (arg->type == 'X')
		res = create_and_fill_bigx(arg);
	else if (arg->type == 's')
		res = create_and_fill_s(arg);
	else if (arg->type == '%')
		res = create_and_fill_pourcent(arg);
	else if (arg->type == 'p')
		res = create_and_fill_ptr(arg);
	return (res);
}

int		exit_display(char *res, t_arg *begin, t_arg *actual)
{
	int len;

	len = ft_strlen(res);
	if (ft_atoi(actual->value) == 0 && actual->type == 'c')
	{
		free(res);
		free_lst(begin);
		return (1);
	}
	return (0);
}

int		display_str(const char *str, t_arg *begin)
{
	int		i;
	char	*res;
	t_arg	*actual;

	i = 0;
	actual = begin;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] && check_valid_arg(str, i++))
		{
			while (!is_convert(str[i]))
				i++;
			i++;
			res = get_arg(actual);
			ft_putstr_fd(res, 1);
			if (actual->type == 'c' && exit_display(res, begin, actual))
				return (0);
			free(res);
			actual = actual->next;
		}
		while (str[i] && str[i] != '%')
			ft_putchar_fd(str[i++], 1);
	}
	free_lst(begin);
	return (0);
}

t_arg	*next_arg(t_arg *actual)
{
	if (actual->type == '%')
		actual->value = "%";
	actual = actual->next;
	return (actual);
}

int		ft_printf(const char *str, ...)
{
	va_list	ap;
	t_arg	*begin;
	t_arg	*actual;

	begin = verify_and_get_arg(str);
	actual = begin;
	va_start(ap, str);
	while (actual)
	{
		if (actual->mfw_star == -1)
			actual->mfw_star = va_arg(ap, int);
		if (actual->precision_star == -1)
			actual->precision_star = va_arg(ap, int);
		if (is_integer(actual->type))
			actual->value = ft_itoa(va_arg(ap, int));
		else if (actual->type == 'p')
			actual->pointeur = va_arg(ap, unsigned long long int);
		else if (actual->type == 's')
			actual->value = va_arg(ap, char *);
		actual = next_arg(actual);
	}
	va_end(ap);
	finish_to_fill_lst(str, &begin);
	display_str(str, begin);
	return (0);
}
