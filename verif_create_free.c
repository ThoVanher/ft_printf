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

t_arg	*create_addback_t_arg(t_arg **begin)
{
	t_arg	*new;

	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		return (0);
	ft_bzero(new, sizeof(t_arg));
	ft_lstadd_back_a(begin, new);
	return (new);
}

int		check_valid_arg(const char *str, int i)
{
	while (str[i])
	{
		if (is_convert(str[i]))
			return (1);
		if (!(is_flag(str[i]) || ft_isdigit(str[i])))
			return (0);
		(i)++;
	}
	return (0);
}

void	create_or_not_arg(const	char *str, int *i, t_arg **begin)
{
	if (check_valid_arg(str, *i))
	{
		create_addback_t_arg(begin);
		get_type_and_stars(str, i, begin);
	}
	else
	{
		while (str[*i] && !is_convert(str[*i]))
			(*i)++;
		(*i)++;
	}
}

t_arg	*verify_and_get_arg(const char *str)
{
	int		i;
	t_arg	**begin;
	t_arg	*tmp;

	tmp = 0;
	begin = &tmp;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			create_or_not_arg(str, &i, begin);
		}
		else
			i++;
	}
	if (*begin == 0)
		create_addback_t_arg(begin);
	return (*begin);
}

void	free_lst(t_arg *begin)
{
	t_arg	*actual;

	actual = begin;
	while (actual)
	{
		if (actual->type != 's' && actual->type != '%')
			free(actual->value);
		actual = actual->next;
		free(begin);
		begin = actual;
	}
	free(actual);
}
