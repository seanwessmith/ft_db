/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 22:53:06 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/10 16:56:08 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*str;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc(sizeof(*str) * (ft_strlen(s) + 1));
	i = 0;
	if (str)
	{
		while (*s)
		{
			str[i] = f(*s);
			s++;
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
