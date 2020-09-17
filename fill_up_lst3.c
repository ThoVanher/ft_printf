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

int		mfw_if_point2(const char *str, t_arg *arg, int i)
{
	while (str[i] != '%')
	{
		if (str[i] == '*')
		{
			arg->mfw = arg->mfw_star;
			return (0);
		}
		else if (ft_isdigit(str[i]))
		{
			while (ft_isdigit(str[i]))
				i--;
			convert_mfw_precision(str, arg, i + 1, 1);
			return (0);
		}
		i--;
	}
	return (1);
}

char	*you_are_zero_dixu2(t_arg *arg, char *res)
{
	int	i;

	i = 0;
	if (!arg->mfw)
		res[0] = '\0';
	while (arg->mfw-- > 0)
		res[i++] = ' ';
	return (res);
}
