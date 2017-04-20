/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:07:06 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 15:56:36 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		*ft_intrealloc(int *ptr, size_t size)
{
	int		*arr;

	if (ptr)
		arr = (int *)malloc(sizeof(int) * size);
	else
		arr = (int *)malloc(size);
	ft_memcpy(arr, ptr, sizeof(int) + 1);
	if (ptr)
		free(ptr);
	return (arr);
}
