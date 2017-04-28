/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selecters.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 18:54:58 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 20:01:56 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "db.h"

void	select_columns_from_table(char *line, t_apple *apple)
{
	printf("database: %s\n", apple->db_name);
	printf("table->name: %s\n", apple->table->name);
	printf("line: %s\n", line);
}

void	select_all_from_table(char *table, t_apple *apple)
{
	int		fd;
	char	*line;
	size_t	line_count;

	line_count = 0;
	line = NULL;
	fd = open_table(table, apple);
	while (get_next_line(fd, &line))
	{
		line_count++;
		if (line_count > 1)
			printf("%s\n", line);
		free(line);
	}
	fd = close(fd);
}

void	select_query(char *line, t_apple *apple)
{
	int		i;
	char	*file;

	i = 1;
	while (!ft_strequ(ft_strupper(ft_strfind(line, i)), "FROM"))
		i++;
	i++;
	if (!apple->db_name)
		printf("No Database selected.\n");
	apple->table = (t_table *)ft_memalloc(sizeof(t_table));
	apple->table->name = ft_strfind(line, i);
	file = apple->db_name;
	file = ft_strjoin(file, "/");
	file = ft_strjoin(file, apple->table->name);
	if (access(file, F_OK) != -1)
	{
		if (ft_strequ(ft_strfind(line, 2), "*"))
			select_all_from_table(ft_strfind(line, i), apple);
		else
			select_columns_from_table(line, apple);
	}
	else
		printf("Table not found.\n");
}
