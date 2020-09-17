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

void	ft_lstadd_back_a(t_arg **alst, t_arg *new)
{
	t_arg	*actual;

	if (!alst || !new)
		return ;
	if (!(*alst))
		(*alst) = new;
	else
	{
		actual = ft_lstlast_a((*alst));
		actual->next = new;
	}
}

t_arg	*ft_lstlast_a(t_arg *lst)
{
	t_arg	*last;

	if (!lst)
		return (lst);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}
