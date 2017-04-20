/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 11:57:40 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/09 20:27:52 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned long long	x;
	int					i;
	int					mn;

	i = 0;
	x = 0;
	mn = 1;
	while (BLANK(str[i]))
		str++;
	if (str[i] == '-' || str[i] == '+')
	{
		mn = str[i] == '-' ? -1 : 1;
		str++;
	}
	while (*str == '0')
		str++;
	while (str[i] != '\0')
	{
		if (str[i] > 57 || str[i] < 48)
			return (mn * x);
		x = x * 10 + str[i++] - '0';
	}
	if (i > 19 || x > 9223372036854775807ULL)
		return (mn == 1 ? -1 : 0);
	return (mn * x);
}
