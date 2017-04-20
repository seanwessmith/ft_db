/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 21:27:12 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/09 22:59:29 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (temp == NULL)
		return (NULL);
	ft_strcpy(temp, s1);
	return (temp);
}
