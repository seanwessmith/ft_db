/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiva <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:00:45 by jpiva             #+#    #+#             */
/*   Updated: 2017/04/29 16:16:56 by jpiva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		no_nl(char **str, char **line, int ret)
{
	int	count;

	count = 0;
	*line = ft_strdup(*str);
	count = ft_strlen(*str);
	ft_strdel(str);
	if (ret == 0)
	{
		if (count > 0)
			return (1);
		else
		{
			*line = NULL;
			return (0);
		}
	}
	return (1);
}

int		nl_found(char **str, char **line, char *nl_pos)
{
	char	*temp;

	*line = ft_strsub(*str, 0, nl_pos - *str);
	temp = ft_strsub(*str, nl_pos - *str + 1, ft_strlen(nl_pos) - 1);
	ft_strdel(str);
	*str = temp;
	return (1);
}

int		copy_lines(int ret, char *buf, char **str)
{
	char	*tmp;

	tmp = NULL;
	if (ret < 0)
		return (-1);
	buf[ret] = '\0';
	if ((*str) != NULL)
	{
		tmp = ft_strjoin(*str, buf);
		ft_strdel(str);
	}
	else
		tmp = ft_strdup(buf);
	*str = tmp;
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char		*s[1025];
	int				ret;
	char			*buf;

	ret = 0;
	if (fd < 0 || BUFF_SIZE < 1 || !line || !(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	while (s[fd] == NULL || (!(ft_strchr(s[fd], '\n')) &&
			(ret = read(fd, buf, BUFF_SIZE))))
		if (copy_lines(ret, buf, &s[fd]) == -1)
			return (-1);
	ft_strdel(&buf);
	if (ft_strchr(s[fd], '\n') && s[fd] != NULL)
		return (nl_found(&s[fd], line, ft_strchr(s[fd], '\n')));
	else if (!(ft_strchr(s[fd], '\n')) && s[fd] != NULL)
		return (no_nl(&s[fd], line, ret));
	return (-1);
}
