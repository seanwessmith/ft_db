/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 20:00:12 by ssmith            #+#    #+#             */
/*   Updated: 2016/11/15 18:31:00 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_maxword(char const *str1, char c, int *word_ct, int *char_ct)
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

static char	**ft_strbuild(char const *str1, char **str2, char c, int *word_ct)
{
	int		i;
	int		max;
	int		char_ct;

	i = 0;
	max = 0;
	char_ct = 0;
	while (str1[i])
	{
		if (str1[i] == c && max == 0 && char_ct > 0)
		{
			str2[*word_ct][char_ct] = '\0';
			max = 1;
			char_ct = 0;
			(*word_ct)++;
		}
		if (str1[i] != c)
		{
			str2[*word_ct][char_ct++] = str1[i];
			max = 0;
		}
		i++;
	}
	str2[*word_ct][char_ct] = '\0';
	return (str2);
}

static char	**ft_append_null(char **str, int word_ct)
{
	if (word_ct == 0 || ft_isalpha(str[word_ct][0]))
		word_ct++;
	str[word_ct] = NULL;
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		max;
	int		char_ct;
	int		word_ct;
	char	**str;

	if (!s)
		return (NULL);
	char_ct = 0;
	max = ft_maxword(s, c, &word_ct, &char_ct);
	str = (char **)malloc(sizeof(char *) * word_ct);
	if (!str)
		return (NULL);
	if (max <= 1)
	{
		str[0] = NULL;
		return (str);
	}
	i = -1;
	while (i++ < word_ct - 1)
		str[i] = (char *)malloc(sizeof(char) * max + 1);
	word_ct = 0;
	str = ft_strbuild(s, str, c, &word_ct);
	str = ft_append_null(str, word_ct);
	return (str);
}
