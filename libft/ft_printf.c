/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:10:43 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:40:15 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	integrate(t_algo *algo)
{
	if (algo->flag != 0)
		run_flag(algo);
	if (algo->width != 0 || algo->precision != 0)
		run_width(algo);
	if (algo->spec != 0)
		run_spec(algo);
	algo->width -= ft_strlen(algo->arg_str);
	while (algo->flag == '-' && (algo->width)-- > 0)
		ft_strncat(algo->arg_str, " ", 1);
}

void	init(t_algo *algo)
{
	algo->null_terminator = 0;
	algo->spaces = 0;
	algo->flag = 0;
	algo->flagh = 0;
	algo->width = 0;
	algo->precision = 0;
	algo->spec = 0;
	algo->length = ft_strnew(0);
	algo->arg_str = ft_strnew(0);
}

void	nucleus(t_algo *algo)
{
	while (algo->in[algo->in_i] != '\0')
	{
		if (algo->in[algo->in_i] != '%')
		{
			ft_strncat(algo->out_str, &(algo->in[algo->in_i]), 1);
			ft_putchar(algo->in[algo->in_i]);
		}
		if (algo->in[algo->in_i] == '%')
		{
			find_flag(algo);
			find_width(algo);
			find_length(algo);
			find_spec(algo);
			integrate(algo);
			ft_putstr(algo->arg_str);
			if (algo->spec == 'c' && algo->null_terminator == 1)
			{
				ft_putchar('\0');
				ft_strcat(algo->arg_str, "0");
			}
			ft_strcat(algo->out_str, algo->arg_str);
			init(algo);
		}
		algo->in_i++;
	}
}

int		ft_printf(const char *fmt, ...)
{
	t_algo	algo;

	va_start(algo.ap, fmt);
	algo.in = (char *)fmt;
	algo.out_str = ft_strnew(0);
	algo.in_i = 0;
	init(&algo);
	nucleus(&algo);
	return (ft_strlen(algo.out_str));
}
