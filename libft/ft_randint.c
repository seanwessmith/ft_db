/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 13:50:03 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/09 16:35:30 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

uintmax_t	ft_randint(int length)
{
	uintmax_t	rand;
	uintmax_t	ret;

	ret = 0;
	while (ft_nbrlen(ret) < length || ret == 0)
	{
		rand = ft_rand();
		rand = ft_hash(rand);
		ret *= 10;
		ret += rand % 10;
	}
	return (ret);
}
