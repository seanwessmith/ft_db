/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:10:41 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 15:57:15 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_chrrealloc(char *ptr, size_t size)
{
	char	*str;

	if (ptr)
		str = (char *)malloc(size * ft_strlen(ptr));
	else
		str = (char *)malloc(size);
	ft_memcpy(str, ptr, ft_strlen(ptr) + 1);
	if (ptr)
		free(ptr);
	return (str);
}
