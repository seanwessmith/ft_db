/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:57:05 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:41:03 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	run_width(t_algo *algo)
{
	if ((algo->flag == 0 || algo->flag == ' ' ||
				algo->flag == '+' ||
				algo->flag == '#') && algo->width > algo->precision)
		while ((int)ft_strlen(algo->arg_str) < algo->width)
			ft_strcat(algo->arg_str, " ");
	if (algo->flag == '0' && algo->width > algo->precision)
		while ((int)ft_strlen(algo->arg_str) < algo->width)
			ft_strcat(algo->arg_str, "0");
	if (algo->precision != 0 && algo->precision > algo->width)
		while ((int)ft_strlen(algo->arg_str) < algo->precision)
			ft_strcat(algo->arg_str, "0");
}

void	run_flag(t_algo *algo)
{
	if (algo->flag == ' ' && algo->spec != 0)
		ft_strncat(algo->arg_str, " ", 1);
}

void	run_spec(t_algo *algo)
{
	if (algo->spec == 's' || algo->spec == 'S')
		arg_str(algo);
	if (algo->spec == 'd' || algo->spec == 'D' ||
			algo->spec == 'i' || algo->spec == 'u' || algo->spec == 'U')
		arg_nbr(algo);
	if (algo->spec == 'c' || algo->spec == 'C')
		arg_char(algo);
	if (algo->spec == 'x' || algo->spec == 'X' || algo->spec == 'p')
		arg_hex(algo);
	if (algo->spec == 'o' || algo->spec == 'O')
		arg_octal(algo);
}
