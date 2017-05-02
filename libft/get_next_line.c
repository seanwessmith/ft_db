/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 10:18:23 by ssmith            #+#    #+#             */
/*   Updated: 2017/03/03 23:54:31 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_linecpy(char *str, char *buf, t_gnl **data, int type)
{
	int		i;

	i = 0;
	while (*str)
		str++;
	while (i < (*data)->buffsize && *buf != '\n')
	{
		*str = *buf;
		str++;
		buf++;
		i++;
	}
	*str = '\0';
	if (*buf == '\n' || (*buf != '\n' && i < BUFF_SIZE && type == 2))
		(*data)->newline = 0;
	else
		++((*data)->newline);
	str--;
	if (i == 0 && ft_strlen(str) == 0)
		(*data)->r = 0;
	if (buf[0] == '\n')
		(*data)->r = 1;
}

char	*ft_buffsave(char *buf, int size)
{
	int		nbr;
	int		i;
	char	*buffsave;

	nbr = 0;
	i = 0;
	buffsave = NULL;
	while (*buf != '\n' && i < size)
	{
		buf++;
		i++;
	}
	buf++;
	if (*buf && i < size)
		buffsave = ft_memalloc((size - i + 1));
	while (i < size - 1 && *buf && *buf != '\0')
	{
		buffsave[nbr] = *buf;
		buf++;
		nbr++;
		i++;
	}
	if (buffsave != NULL)
		buffsave[nbr] = '\0';
	return (buffsave);
}

t_gnl	*find_buf(char ***str, t_gnl *data)
{
	if (!data)
	{
		data = (t_gnl *)malloc(sizeof(t_gnl));
		data->buffsave = NULL;
	}
	data->newline = 1;
	data->r = 0;
	**str = NULL;
	if (data->buffsave)
	{
		data->r = 1;
		**str = ft_memalloc((BUFF_SIZE * data->newline)
				+ ft_strlen(data->buffsave));
		data->buffsize = ft_strlen(data->buffsave);
		ft_linecpy(**str, data->buffsave, &data, 1);
		data->buffsave = ft_buffsave(data->buffsave, data->buffsize);
	}
	return (data);
}

int		get_next_line(const int fd, char **line)
{
	int				i;
	char			buf[BUFF_SIZE + 1];
	static t_gnl	*data;

	printf("------GNL START\n");
	if (fd < 0 || line == NULL)
		return (-1);
	data = find_buf(&line, data);
	if (data->newline == 0)
		return (1);
	printf("data->newline: %d\n", data->newline);
	while (data->newline > 0 && (i = read(fd, buf, BUFF_SIZE)) > 0)
	{
		printf("loop\n");
		data->r = 1;
		data->buffsize = i;
		buf[i] = 0;
		*line = (data->newline > 1) ? ft_realloc(*line, i + 1) : ft_memalloc(i);
		if (data->newline > 0)
			ft_linecpy(*line, buf, &data, 2);
		if (data->newline <= 0)
			data->buffsave = ft_buffsave(buf, data->buffsize);
	}
	printf("------GNL END\n");
	return (i == -1) ? -1 : data->r;
}
