/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:38:35 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/11 21:08:16 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t		x;
	size_t		y;
	size_t		end;
	char		*str;

	x = 0;
	y = 0;
	if (!s)
		return (NULL);
	while ((s[x] == ' ' || s[x] == '\n' || s[x] == '\t') && s[x] != '\0')
		x++;
	end = ft_strlen(s) - 1;
	while (end > x && (s[end] == ' ' || s[end] == '\n' || s[end] == '\t'))
		end--;
	str = (char *)malloc(sizeof(char) *
			(ft_strlen(s) - (ft_strlen(s) - end + x)) + 2);
	if (!str)
		return (NULL);
	while (x < end + 1)
		str[y++] = s[x++];
	str[y] = '\0';
	return (str);
}
