/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_chr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:55:06 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:41:15 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	arg_str(t_algo *algo)
{
	wchar_t		*str;

	str = NULL;
	str = va_arg(algo->ap, wchar_t*);
	if (str && ft_findchr("sS", algo->spec))
	{
		if (algo->precision > 0 && algo->spec == 's'
				&& !ft_strequ(algo->length, "l") && algo->flagm == '-')
			prechrcat(algo->arg_str, (char *)str, algo->precision);
		else if (algo->precision > 0 && algo->spec == 's'
				&& !ft_strequ(algo->length, "l"))
			ft_strncat(algo->arg_str, (char*)str, algo->precision);
		else if (algo->spec == 's' && !ft_strequ(algo->length, "l"))
			ft_strcat(algo->arg_str, (char*)str);
		else
			while (*str)
				ft_strwcat(algo->arg_str, *str++);
		adjuster(algo);
		while (algo->precision-- > 0 && algo->arg_str[0] == '0')
			debuff(algo);
	}
	else
		ft_strcat(algo->arg_str, "(null)");
}

void	arg_char(t_algo *algo)
{
	char	c;
	wchar_t	wc;

	c = 0;
	wc = 0;
	if (algo->spec == 'c')
	{
		c = va_arg(algo->ap, int);
		algo->arg_str[ft_strlen(algo->arg_str)] = c;
	}
	else if (algo->spec == 'C')
	{
		wc = va_arg(algo->ap, wint_t);
		algo->arg_str[ft_strlen(algo->arg_str)] = wc;
	}
	algo->arg_str[ft_strlen(algo->arg_str) + 1] = '\0';
	if (c == 0 && wc == 0)
	{
		debuff(algo);
		algo->null_terminator = 1;
	}
	while (algo->precision-- > 0)
		debuff(algo);
	adjuster(algo);
}

void	ft_strbeg(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strdup(s1);
	ft_strcpy(s1, s2);
	ft_strcat(s1, temp);
}

char	*prechrcat(char *s1, char *s2, int precision)
{
	char	*temp;

	temp = ft_strnew(0);
	temp = ft_strdup(s1);
	ft_bzero(s1, ft_strlen(s1) + ft_strlen(temp));
	ft_strncat(s1, s2, precision);
	ft_strcat(s1, temp);
	free(temp);
	return (s1);
}

void	asterisk(t_algo *algo, int type)
{
	if (type == 1)
	{
		algo->width = va_arg(algo->ap, int);
		algo->flag = ' ';
	}
	else
	{
		algo->precision = va_arg(algo->ap, int);
		algo->in_i++;
	}
}
