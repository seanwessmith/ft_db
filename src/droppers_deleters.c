/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dropers_deleters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:39:58 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 09:40:06 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "db.h"

char	*ft_strfind(char *input, int w_count)
{
    char	*ret;
    int		i;

    ret = ft_strnew(0);
	i = 0;
	while (w_count > 1 && *input)
	{
		if (*input == ' ')
			w_count--;
		input++;
	}
	while (input[i] && input[i] != ' ')
		i++;
	ret = (char *)ft_memalloc(sizeof(char) * i);
	i = 0;
	while ((ret[i] = *input) && *input)
	{
        if (*(input + 1) == ' ' || *(input + 1) == '\0')
            return (ret);
        i++;
        input++;
    }
	return (NULL);
}

static int rmFiles(const char *dir, const struct stat *sbuf, int type, struct FTW *ftwb)
{
	(void)sbuf;
	(void)type;
	(void)ftwb;
	if(remove(dir) < 0)
	{
		perror("ERROR: remove");
		return (-1);
	}
	return (0);
}

void	drop_query(char *line, t_apple *apple)
{
	if (line && ft_strequ(ft_strupper(ft_strfind(line, 2)), "TABLE"))
	{
		if (apple->db_name)
			printf("No db selected\n");
		else
		{
			if (check_table(ft_strfind(line, 3), apple))
				drop_table(line, apple);
			else
				printf("Table not found\n");
		}
	}
	else if (line && ft_strequ(ft_strupper(ft_strfind(line, 2)), "DATABASE"))
		drop_database(line, apple);
}


void	delete_query(char *line)
{
	line = NULL;
	write(0, "delete\n", 8);

}

void	drop_table(char *line, t_apple *apple)
{
	int ret;
	char *table;

	table = ft_strnew(ft_strlen(apple->db_name) + ft_strlen(ft_strfind(line, 3) + 2));
	table = ft_strjoin(apple->db_name, "/");
	table = ft_strjoin(table, ft_strfind(line, 3));

	ret = remove(table);
	printf("ret:%d\n", ret);

	if (ret == 0)
		printf("Table delete successfully\n");
	else
		printf("Failed to delete table");
}

void	drop_database(char *line, t_apple *apple)
{
	if (!apple->db_name)
		printf("Error son, no db selected! Fuck!\n");
	else if (ft_strequ(ft_strupper(ft_strfind(line, 3)), apple->db_name))
	{
		if (nftw(apple->db_name, rmFiles, 10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) < 0)
			printf("FACK the shit wasn't delorted!\n");
		else
			printf("Deleted yer shit, boss!\n");
	}
	else
		printf("Not a database\n");
}

int		column_count(char *line)
{
	int column_count;
	int i;

	i = 0;
	column_count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ')' && (line[i + 1] == ',' || line[i + 1] == ']'))
			column_count++;
		i++;
	}
	return (column_count);
}

void	select_all_from_table(char *table, t_apple *apple)
{
	int fd;
	char *line;
	size_t line_count;

	line_count = 0;
	line = NULL;
	fd = open_table(table, apple);
	while(get_next_line(fd, &line))
	{
		line_count++;
		if (line_count > 1)
			printf("%s\n",line);
		free(line);
	}
	fd = close(fd);
}

void	select_columns_from_table(char *line, char *table, t_apple *apple)
{
	printf("select columns from table\n");

	int 	fd;
	char	*line2;
	size_t	line_count;
	char	column[50];

	fd = open_table(table, apple);
	line_count = 0;
	get_next_line(fd, &line2);

	printf("%d\n",column_count(line));
	int which_columns[column_count(line2)];

	(void)which_columns;
	int x;
	int y;
	x = 0;
	while(line2[x] != '\0')
	{
		if (line2[x] == '(')
		{
			x++;
			y = 0;
			while(line2[x] != ',')
			{
				column[y] = line2[x];
				y++;
				x++;
			}
			column[y] = '\0';
			printf("column:%s\n",column);
		}
		x++;
	}

	while(get_next_line(fd, &line2))
	{
		line_count++;
		if (line_count > 1)
		{

		}
		free(line2);
	}
	fd = close(fd);
}
