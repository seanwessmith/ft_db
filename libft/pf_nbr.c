/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:54:00 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:41:23 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	arg_int(t_algo *algo, long long d)
{
	if (algo->flag == '+' && d >= 0)
		ft_strncat(algo->arg_str, "+", 1);
	if (d < 0 && d >= -2147483647)
	{
		if (algo->arg_str[0] == '+' && algo->width == 0)
			algo->arg_str = ft_strnew(0);
		if (ft_lastchr(algo->arg_str) == ' ')
			algo->arg_str[ft_strlen(algo->arg_str) - 1] = '-';
		else if (algo->flag != '0')
			ft_strcat(algo->arg_str, "-");
		else
			algo->arg_str[0] = '-';
		if (algo->precision > 0)
			algo->precision++;
		d *= -1;
	}
	if (algo->precision >= (int)ft_strlen(ft_itoa(d))
			&& algo->precision < algo->width)
		flipflag(algo);
	if (algo->precision < algo->width && algo->precision > 0)
		ft_strcat(algo->arg_str, ft_pad(ft_itoa(d),
					algo->precision + algo->spaces));
	else
		ft_strcat(algo->arg_str, ft_itoa(d));
}

void	adjuster(t_algo *algo)
{
	if (algo->spec == 's' && algo->flagm == '-')
		revdebuff(algo);
	else if (algo->precision > algo->width && algo->precision > 0
			&& algo->precision < (int)ft_strlen(algo->arg_str))
		while ((int)ft_strlen(algo->arg_str) > algo->precision + algo->spaces)
			debuff(algo);
	else if (algo->width > algo->precision && algo->width > 0)
		while ((int)ft_strlen(algo->arg_str) > algo->width && debuff(algo))
			;
}

void	arg_nbr(t_algo *algo)
{
	long long				ll;
	unsigned long long int	u;
	int						subtract;

	subtract = 0;
	if (algo->spec == 'u' || algo->spec == 'U')
	{
		if (ft_findchr("jlhz", algo->length[0]) || algo->spec == 'U')
			u = va_arg(algo->ap, unsigned long long int);
		else
			u = va_arg(algo->ap, unsigned int);
		ft_strcat(algo->arg_str, ft_itoau(u));
	}
	else if (ft_findchr("hhlljz", algo->length[0]) || algo->spec == 'D')
	{
		ll = va_arg(algo->ap, long long);
		ft_strcat(algo->arg_str, ft_itoal(ll));
	}
	else
	{
		if ((ll = va_arg(algo->ap, int)) == 0 && algo->precision == -1)
			return ;
		arg_int(algo, ll);
	}
	adjuster(algo);
}

void	arg_hex(t_algo *algo)
{
	uintmax_t		j;
	unsigned long	l;

	if (ft_strequ(algo->length, "j"))
	{
		j = va_arg(algo->ap, uintmax_t);
		ft_strcat(algo->arg_str, ft_strlower((ft_itoa_basel(j, 16))));
	}
	else
	{
		l = va_arg(algo->ap, long);
		if ((l != 0 && algo->flagh == '#') || algo->spec == 'p')
			ft_strcat(algo->arg_str, "0x");
		ft_strcat(algo->arg_str, ft_strlower((ft_itoa_basel(l, 16))));
		if (algo->spec == 'X')
			ft_strupper(algo->arg_str);
	}
	if (algo->width > algo->precision)
		while ((int)ft_strlen(algo->arg_str) > algo->width && debuff(algo))
			;
	if (algo->precision > algo->width)
		while ((int)ft_strlen(algo->arg_str) > algo->precision && debuff(algo))
			;
}

void	arg_octal(t_algo *algo)
{
	unsigned long	l;

	l = va_arg(algo->ap, long);
	if (l != 0 && algo->flagh == '#')
		ft_strcat(algo->arg_str, "0");
	if (algo->precision > (int)ft_strlen(ft_itoa(l)) && algo->precision > 0)
		ft_pad(algo->arg_str, algo->precision);
	if (algo->precision > 0)
		ft_strcat(algo->arg_str, ft_pad(ft_itoa_basel(l, 8), algo->precision));
	else if (algo->precision != -1)
		ft_strcat(algo->arg_str, ft_itoa_basel(l, 8));
	if (algo->width > algo->precision)
		while ((int)ft_strlen(algo->arg_str) > algo->width && debuff(algo))
			;
	if (algo->precision > algo->width)
		while ((int)ft_strlen(algo->arg_str) > algo->precision && debuff(algo))
			;
}
