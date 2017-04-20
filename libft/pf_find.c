/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:56:01 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:41:20 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	find_width(t_algo *algo)
{
	if (ft_isdigit(algo->in[algo->in_i - 1]))
		algo->in_i--;
	while (ft_isdigit(algo->in[algo->in_i]))
	{
		algo->width *= 10;
		algo->width += algo->in[algo->in_i++] - '0';
	}
	if (ft_findnchr(algo->in, '*', algo->in_i - 2, algo->in_i))
		asterisk(algo, 1);
	if (algo->in[algo->in_i] == '.')
	{
		algo->in_i++;
		if (algo->in[algo->in_i] == '*')
			asterisk(algo, 2);
		else
			while (ft_isdigit(algo->in[algo->in_i]))
			{
				algo->precision *= 10;
				algo->precision += algo->in[algo->in_i] - '0';
				algo->in_i++;
			}
		if (algo->precision == 0)
			algo->precision = -1;
	}
}

void	find_flag(t_algo *algo)
{
	algo->in_i++;
	while (ft_findchr(" +#0-*+", algo->in[algo->in_i])
			&& algo->in[algo->in_i] != '\0')
	{
		if (algo->in[algo->in_i] == ' ')
			algo->spaces++;
		if (algo->in[algo->in_i + 1] == '+' && algo->flag == '+')
			ft_strcat(algo->arg_str, "+");
		if (algo->in[algo->in_i] == '#')
			algo->flagh = algo->in[algo->in_i];
		if (algo->in[algo->in_i] == '+' && algo->flag == '0')
			ft_strcat(algo->arg_str, "+");
		if (algo->in[algo->in_i] == '+' && algo->flag == '-')
			ft_strcat(algo->arg_str, "+");
		if (algo->in[algo->in_i - 1] == '-' || algo->in[algo->in_i] == '-')
			algo->flag = '-';
		else if (!(algo->in[algo->in_i] == '0' && algo->flag == '-') &&
				(!(algo->in[algo->in_i] == ' ' && algo->flag == '+')) &&
				(!(algo->in[algo->in_i] == '+' && algo->flag == '0')) &&
				(algo->in[algo->in_i] != '#'))
			algo->flag = algo->in[algo->in_i];
		if (algo->in[algo->in_i - 1] == '-' || algo->in[algo->in_i] == '-')
			algo->flagm = '-';
		algo->in_i++;
	}
}

void	find_length(t_algo *algo)
{
	while (algo->in[algo->in_i] == 'h' && ++algo->in_i)
		ft_strcat(algo->length, "h");
	while (algo->in[algo->in_i] == 'l' && ++algo->in_i)
		ft_strcat(algo->length, "l");
	if (algo->in[algo->in_i] == 'j')
		ft_strcat(algo->length, "j");
	if (algo->in[algo->in_i] == 'z')
		ft_strcat(algo->length, "z");
	if (algo->in[algo->in_i] == 't')
		ft_strcat(algo->length, "t");
	if (ft_findchr("jzt", *(algo->length)))
		algo->in_i++;
}

void	find_spec(t_algo *algo)
{
	while (algo->in[algo->in_i] == ' ')
		algo->in_i++;
	if (algo->in[algo->in_i] == '%')
	{
		run_width(algo);
		ft_strrcat(algo->arg_str, "%", algo->width - 1);
	}
	if (ft_findchr("psSdDiuUcCxXoO", algo->in[algo->in_i]))
		algo->spec = algo->in[algo->in_i];
}
