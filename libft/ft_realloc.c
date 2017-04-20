/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 15:52:29 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:58:12 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_realloc(char *ptr, size_t size)
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
