/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 16:26:45 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 11:35:15 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strupper(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	if (!str)
		return (NULL);
	ret = (char *)ft_memalloc(sizeof(str));
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			ret[i] = str[i] - 32;
		else
			ret[i] = str[i];
		i++;
	}
	return (ret);
}
