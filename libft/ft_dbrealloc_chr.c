/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbrealloc_chr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 15:52:29 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 15:57:47 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbrealloc_chr(char **ptr, size_t size)
{
	int		i;
	char	**ret;

	i = -1;
	ret = (char **)ft_memalloc(sizeof(char *) * size);
	while (ptr[++i])
	{
		ret[i] = ft_strnew(0);
		ret[i] = ft_strjoin(ret[i], ptr[i]);
	}
	return (ret);
}
