/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_adjust.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:52:55 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/24 14:41:10 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		debuff(t_algo *algo)
{
	int		spaces;
	int		i;
	int		x;

	i = 0;
	x = 0;
	spaces = algo->spaces;
	if (!ft_findchr(" 0-+", algo->arg_str[i]))
		return (0);
	while ((!ft_findchr(" 0", algo->arg_str[i])
				&& algo->arg_str[i]) || spaces > 0)
	{
		i++;
		spaces--;
	}
	if (algo->arg_str[i] == '\0')
		return (0);
	while (algo->arg_str[i + 1] != '\0')
	{
		algo->arg_str[i] = algo->arg_str[i + 1];
		i++;
	}
	algo->arg_str[i] = '\0';
	return (1);
}

void	revdebuff(t_algo *algo)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_memalloc(ft_strlen(algo->arg_str) - algo->width + 10);
	while (i < algo->width)
	{
		temp[i] = algo->arg_str[i];
		i++;
	}
	temp[i] = '\0';
	algo->arg_str = ft_memalloc(ft_strlen(algo->arg_str) - algo->width + 10);
	ft_strcpy(algo->arg_str, temp);
	free(temp);
}

char	*ft_pad(char *str, int size)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strnew(0);
	while (i + (int)ft_strlen(str) < size)
	{
		ft_strcat(temp, "0");
		i++;
	}
	temp = ft_strcat(temp, str);
	ft_strcat(temp, "\0");
	ft_bzero(str, size + ft_strlen(temp));
	ft_strcat(str, temp);
	free(temp);
	return (str);
}

char	*ft_padend(char *str, int size)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strnew(0);
	str = ft_strcat(temp, str);
	while (i + (int)ft_strlen(str) < size)
	{
		ft_strcat(temp, "0");
		i++;
	}
	free(temp);
	return (str);
}

void	flipflag(t_algo *algo)
{
	int		i;

	i = 0;
	while (algo->arg_str[i])
	{
		if (algo->arg_str[i] == '0')
			algo->arg_str[i] = ' ';
		i++;
	}
}
