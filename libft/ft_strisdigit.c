/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 10:56:31 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 17:09:51 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strisdigit(char *str, int type)
{
	while (*str != '\0')
	{
		if (type == 1)
		{
			if (*str < 48 || *str > 57)
				return (0);
		}
		else if ((*str < 48 || *str > 57)
				&& *str != ' ' && *str != '-')
			return (0);
		str++;
	}
	return (1);
}
