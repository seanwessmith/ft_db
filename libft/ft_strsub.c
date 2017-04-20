/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:19:44 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/10 20:13:35 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*str;

	i = 0;
	if (s)
	{
		if (len > (ft_strlen(s) - start))
			return (NULL);
		str = (char *)malloc(sizeof(char) * len + 1);
		if (str)
		{
			while (s[start] && i < len)
			{
				str[i] = s[start];
				i++;
				start++;
			}
			str[i] = '\0';
		}
		return (str);
	}
	return (NULL);
}
