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

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct				s_arg
{
	int						minus;
	int						zero;
	int						mfw;
	int						mfw_star;
	int						point;
	int						precision;
	int						precision_star;
	char					type;
	char					*value;
	unsigned long long int	pointeur;
	int						tmp;
	struct s_arg			*next;
}							t_arg;

typedef struct				s_res
{
	int						minus;
	int						nb_zero;
	int						nb_space;
}							t_res;

void						ft_lstadd_back_a(t_arg **alst, t_arg *new1);
t_arg						*ft_lstlast_a(t_arg *lst);
t_arg						*create_addback_t_arg(t_arg **begin);
t_arg						*verify_and_get_arg(const char *str);
int							check_valid_arg(const char *str, int i);
void						finish_to_fill_lst(const char *str, t_arg **begin);
void						get_type_and_stars(const char *str, int *i,
							t_arg **begin);
int							is_flag(char c);
void						convert_mfw_precision(const char *str,
							t_arg *arg, int i, int j);
void						get_mfw_precision(const char *str, t_arg *arg,
							int i);
int							is_convert(char c);
char						*you_are_zero_dixu(t_arg *arg, char *res, t_res a);
char						*you_are_zero_dixu2(t_arg *arg, char *res);
char						*create_and_fill_di(t_arg *arg);
char						*create_and_fill_x(t_arg *arg);
char						*create_and_fill_bigx(t_arg *arg);
char						*create_and_fill_u(t_arg *arg);
char						*create_and_fill_c(t_arg *arg);
char						*create_and_fill_s(t_arg *arg);
char						*create_and_fill_ptr(t_arg *arg);
char						*create_and_fill_pourcent(t_arg *arg);
int							max_width_field_dixu(t_arg *arg);
char						*if_minus_dixu(t_arg *arg, char *res, t_res a);
char						*if_no_minus_dixu(t_arg *arg, char *res, t_res a);
t_res						no_minus_0_space_dixu(t_arg *arg, t_res a, int len);
t_res						minus_0_space_dixu(t_arg *arg, t_res a, int len);
t_res						get_space_s(t_arg *arg, t_res a);
char						conv_int_to_char(t_arg *arg);
char						*ft_convert_base_x(t_arg *arg);
long						ft_atoi_base_xu(char *str, char *base);
char						*ft_itoa_base_xu(long nbr, char *base_to);
int							nb_digit_ptr(unsigned long long int nbr,
									char *base_to);
char						*convert_ptr(unsigned long long int nbr, char *res,
									char *base_to);
int							ft_printf(const char *str, ...);
void						free_lst(t_arg *begin);
void						afflst_arg(t_arg **begin);
int							mfw_if_point2(const char *str, t_arg *arg, int i);
void						*ft_memset(void *b, int c, size_t len);
void						*ft_memcpy(void *dst, const void *src, size_t n);
char						*ft_strdup(char *src);
int							ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
