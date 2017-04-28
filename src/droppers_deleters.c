/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   droppers_deleters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:39:58 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 19:59:53 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "db.h"

char	*ft_strfind(char *input, int w_count)
{
    char	*ret;
    int		i;

    ret = ft_strnew(0);
	while (*input == ' ')
		input++;
	while (*input && w_count > 1)
	{
		if (*input == ' ')
			w_count--;
		input++;
	}
	i = 0;
	while (input[i] && input[i] != ' ')
		i++;
	ret = (char *)ft_memalloc(sizeof(char) * (i + 1));
	i = 0;
	while (*input && (ret[i] = *input))
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

void	remove_all_table_records(char *table, t_apple *apple)
{
	int		fd;
	char	*header;
	char	*line;
	char 	*create_file;

	fd = open_table(table, apple);

	get_next_line(fd, &header);
	if (!header)
		printf("File error, missing header\n");
	else
	{
		line = ft_strnew(ft_strlen(table) + 4);
		line = ft_strjoin("1 2 ", table);
		if(drop_table(line, apple) == -1)
			printf("Error clearing table\n");
		else
		{
			fd = close(fd);

			create_file = ft_strnew(ft_strlen(apple->db_name) + ft_strlen(table) + 2);
			create_file = ft_strjoin(apple->db_name, "/");
			create_file = ft_strjoin(create_file, table);

			fd = open(create_file, O_CREAT | O_WRONLY, 0744);
			write(fd, header, ft_strlen(header));
			fd = close(fd);
			printf("Deleted all records from %s\n", table);
		}
	}
}

void	delete_all_records(char *line, t_apple *apple)
{
	if (ft_strfind(line, 3) && check_table(ft_strfind(line, 3), apple) == 1)
		remove_all_table_records(ft_strfind(line, 3), apple);
	else if (ft_strfind(line, 4) && (check_table(ft_strfind(line, 4), apple) == 1))
		remove_all_table_records(ft_strfind(line, 4), apple);
	else
		printf("Table not found.\n");
}

int		drop_table(char *line, t_apple *apple)
{
	int		ret;
	char	*table;

	table = ft_strnew(ft_strlen(apple->db_name) + ft_strlen(ft_strfind(line, 3) + 2));
	table = ft_strjoin(apple->db_name, "/");
	table = ft_strjoin(table, ft_strfind(line, 3));
	ret = remove(table);
	if (ret == 0)
		return(1);
	else
		return(-1);
}

void	delete_query(char *line, t_apple *apple)
{
	if (line && ft_strequ(ft_strfind(line, 2), "*") && !ft_strfind(line, 5))
		delete_all_records(line, apple);
	else if (line && ft_strequ(ft_strupper(ft_strfind(line, 2)),"FROM") && !ft_strfind(line, 5))
		delete_all_records(line, apple);
}

void	drop_database(char *line, t_apple *apple)
{
	if (!apple->db_name)
		printf("No database selected\n");
	else if (ft_strequ(ft_strupper(ft_strfind(line, 3)), apple->db_name))
	{
		if (nftw(apple->db_name, rmFiles, 10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) < 0)
			printf("Failed to drop %s\n", apple->db_name);
		else
			printf("%s database dropped\n", apple->db_name);
	}
	else
		printf("Not a database\n");
}

int	check_table(char *line, t_apple *apple)
{
	char *table;

	table = ft_strnew(ft_strlen(apple->db_name) + ft_strlen(line + 2));
	table = ft_strjoin(apple->db_name, "/");
	table = ft_strjoin(table, line);
	if (access(table, F_OK) != -1)
		return (1);
	else
		return (-1);
}

void	drop_query(char *line, t_apple *apple)
{
	if (line && ft_strequ(ft_strupper(ft_strfind(line, 2)), "TABLE"))
	{
		if (!apple->db_name)
			printf("No db selected\n");
		else
		{
			if (check_table(ft_strfind(line, 3), apple))
				if (drop_table(line, apple) == 1)
					printf("Table dropped successfully\n");
				else
					printf("Failed to drop table\n");
			else
				printf("The %s table does not exist\n", ft_strfind(line, 3));
		}
	}
	else if (line && ft_strequ(ft_strupper(ft_strfind(line, 2)), "DATABASE"))
		drop_database(line, apple);
	else
		printf("Incorrect query.\n");
}
