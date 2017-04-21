/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 15:52:29 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:58:12 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		*ft_realloc_int(int *ptr, size_t size)
{
	size_t	i;
	int		*ret;

	i = 0;
	if (ptr)
		ret = (int *)ft_memalloc(sizeof(int) * size);
	else
		ret = (int *)ft_memalloc(sizeof(int));
	while (i < size)
	{
		ret[i] = ptr[i];
		i++;
	}
	if (ptr)
		free(ptr);
	return (ret);
}
