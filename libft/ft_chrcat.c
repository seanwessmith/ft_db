/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 14:20:55 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/26 21:34:27 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_chrcat(char *s1, const char c)
{
	int		i;
	char	*ret;

	i = 0;
	if ((!c) || !s1)
		return (s1);
	ret = (char *)ft_memalloc(sizeof(char) * (ft_strlen(s1) + 2));
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = c;
	ret[++i] = '\0';
	return (ret);
}
