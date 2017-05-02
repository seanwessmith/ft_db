/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updaters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:58:37 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 19:46:15 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "db.h"

char    *find_value(char *line, char *find)
{
    int     i;
    char    *value;

    line = ft_strstr(line, find);
    line = ft_strchr(line, '\'');
    line++;
    value = (char *)ft_memalloc(sizeof(char) * ft_strlen(line) - 1);
    i = 0;
    while (line[i] && line[i] != '\'')
    {
        value[i] = line[i];
        i++;
    }
    value[i] = '\0';
	write(1, "eA\n", 3);
    return (value);
}

int     *update_column_nums(char *line, char ***values, t_table *table)
{
    int     i;
    int     *cols;
    char    *find;

    i = 0;
    *values = NULL;
    cols = (int *)ft_memalloc(sizeof(int) * table->column_count);
    while (i < table->column_count)
    {
        find = ft_strjoin(table->columns[i], "=");
        *values = ft_dbrealloc_chr(*values, i);
        if (ft_strstr(line, find))
        {
            cols[i] = 1;
            (*values)[i] = find_value(line, find);
        }
        else
            cols[i] = 0;
        i++;
    }
	write(1, "eB\n", 3);
    return (cols);
}

char    *line_builder(char *line, int *cols, t_table *table)
{
    int     i;
    char    *str;

    i = 0;
    str = ft_strdup("[(");
    while (i < table->column_count)
    {
        str = (i == 0) ? str : ft_strjoin(str, ", (");
        if (cols[i] == 1)
            str = ft_strjoin(str, "NULL");
        if (table->column_type[i] == 1 && !cols[i])
            str = ft_strjoin(str, parse_col_char(line, i + 1));
        if (table->column_type[i] == 2 && !cols[i])
            str = ft_strjoin(str, ft_itoa(parse_col_int(line, i + 1)));
        str = ft_strjoin(str, ")");
        i++;
    }
    str = ft_strjoin(str, "]");
	write(1, "eC\n", 3);
    return (NULL);
}

void    run_update(int *cols, int fd, char *file, t_table *table)
{
    int     i;
    int     j;
    char    *line;
    char    **new_file;
	int		num;

    i = 0;
    new_file = NULL;
    while ((num = get_next_line(fd, &line)) > 0)
    {
        new_file = ft_dbrealloc_chr(new_file, i);
        new_file[i] = line_builder(line, cols, table);
        i++;
        free(line);
		write(1, "loop\n", 5);
    }
	printf("end gnl\n");
    j = -1;
    close(fd);
    if ((fd = open(file, O_WRONLY) > 0) > 0)
    {
		printf("fd = %d\n", fd);
        while (j++ < i)
            write(fd, new_file[j], ft_strlen(new_file[j]));
    }
	else
		printf("BAD fd = %d\n", fd);
    printf("The %s table has been updated.\n", table->name);
}

void    update_query(char *line, t_apple *apple)
{
    int     fd;
    int     *cols;
    char    **values;
    char    *file;

    if (apple->db_name && ft_strequ(ft_strupper(ft_strfind(line, 3)), "SET"))
    {
        apple->table = (t_table *)malloc(sizeof(t_table));
        apple->table->name = ft_strfind(line, 2);
        file = ft_strnew(0);
        file = ft_strjoin(apple->db_name, "/");
        file = ft_strjoin(file, apple->table->name);
        if ((fd = open(file, O_RDONLY) != -1))
        {
            parse_table_header(file, apple->table);
            cols = update_column_nums(line, &values, apple->table);
            run_update(cols, fd, file, apple->table);
            printf("done!\n");
        }
        else
            printf("The %s table does not exist.\n", apple->table->name);
    }
    else
        printf("Please enter into a database first.\n");
}
