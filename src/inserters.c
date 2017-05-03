/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inserters.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:39:49 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 16:21:33 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "db.h"

int		parse_insert_string(char **ret, char *line, int col, t_table *table)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	*ret = ft_strjoin(*ret, "(");
	while (*line && *line != '\"')
		line++;
	line++;
	if (*line == '\0')
		return (-1);
	while (*line && *line != '\"' && *line != ')' && i++ <= table->column_length[col])
	{
		*ret = ft_chrcat(*ret, *line);
		line++;
	}
	if (i >= table->column_length[col])
	{
		ft_printf("String would be truncated. The statement has been terminated\n");
		return (-1);
	}
	*ret = ft_strjoin(*ret, ")");
	return (1);
}

int		parse_insert_int(char **ret, char *line)
{
	int		flag;

	flag = 0;
	*ret = ft_strjoin(*ret, "(");
	while (*line && *line == ' ')
		line++;
	while (*line && *line != ',' && *line != ')' && flag == 0)
	{
		if (*line < '0' || *line > '9')
			return (-1);
		else
			*ret = ft_chrcat(*ret, *line);
		line++;
	}
	*ret = ft_strjoin(*ret, ")");
	return (1);
}

char	*parse_insert_record(char *line, t_table *table)
{
	int		flag;
	int		i;
	char	*ret;

	i = -1;
	flag = 0;
	ret = ft_strnew(0);
	while (++i < table->column_count && flag == 0)
	{
		if (i > 0)
			ret = ft_strjoin(ret, ", ");
		if (table->column_type[i] == 1)
		{
			if (parse_insert_string(&ret, line, i, table) == -1)
				return (NULL);
			line = end_string(line);
		}
		else if (table->column_type[i] == 2)
		{
			if (parse_insert_int(&ret, line) == -1)
				return (NULL);
			line = end_int(line);
		}
	}
	return (ret);
}

char	*parse_file(char *line)
{
	char	*gnl;
	char	*ret;
	char	*filename;
	int		fd;

	filename = ft_strfind(line, 6);
	fd = open(filename, O_RDONLY);
	ret = ft_strnew(0);
	while (get_next_line(fd, &gnl))
		ret = ft_strjoin(ret, gnl);
	return (ret);
}

int		parse_insert(char *line, char *file, t_table *table)
{
	int		fd;
	char	*s;

	if (ft_strequ(ft_strfind(line, 5), "file"))
		line = parse_file(line);
	fd = open(file, O_WRONLY | O_APPEND);
	while (*line)
	{
		if (*line == '(')
		{
			line++;
			s = ft_strnew(0);
			s = ft_strjoin(s, "[");
			s = ft_strjoin(s, parse_insert_record(line, table));
			if (s == NULL)
				return (-1);
			s = ft_strjoin(s, "]\n");
			write(fd, s, ft_strlen(s));
		}
		line++;
	}
	return (1);
}

void	insert_query(char *line, t_apple *apple)
{
	char	*file;

	if (apple->db_name)
	{
		apple->table = (t_table *)malloc(sizeof(t_table));
		apple->table->name = ft_strfind(line, 3);
		file = apple->db_name;
		file = ft_strjoin(file, "/");
		file = ft_strjoin(file, apple->table->name);
		if (access(file, F_OK) != -1)
		{
			parse_table_header(file, apple->table);
			if (parse_insert(line, file, apple->table) == 1)
				printf("Records were successfully inserted into the %s table.\n", apple->table->name);
			else
				printf("Records were NOT inserted. Incorrect query format.\n");
		}
		else
			printf("The %s table doesn't exist\n", apple->table->name);
	}
	else
		printf("Records were not inserted. Must enter database first\n");
}
