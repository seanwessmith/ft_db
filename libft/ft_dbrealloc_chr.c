/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbrealloc_chr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 15:52:29 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 14:13:26 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dbrealloc_chr(char **ptr, size_t size)
{
	size_t	i;
	char	**ret;

	i = 0;
	ret = (char **)ft_memalloc(sizeof(char *) * size);
	if (ptr && size != 0)
    {
        while (ptr[i] && i < size)
	    {
	    	ret[i] = ft_strnew(0);
	    	ret[i] = ft_strjoin(ret[i], ptr[i]);
	    	i++;
	    }
    }
    else
        ret[i] = ft_strnew(0);
	return (ret);
}
