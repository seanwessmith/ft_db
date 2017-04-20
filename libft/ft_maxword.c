/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maxword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 10:51:19 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/13 21:32:39 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_maxword(char const *str1, char c, int *word_ct, int *char_ct)
{
	int		i;
	int		delim;
	int		max;

	*word_ct = 1;
	max = 0;
	delim = 0;
	i = 0;
	while (str1[i])
	{
		if (delim == 0)
			(*char_ct)++;
		if (str1[i] == c && delim == 0)
		{
			*char_ct = 0;
			delim = 1;
			(*word_ct)++;
		}
		else if (str1[i] != c)
			delim = 0;
		if (max < *char_ct)
			max = *char_ct;
		i++;
	}
	return (max);
}
