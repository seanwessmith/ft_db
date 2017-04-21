//FT_DB

#include "libft.h"

char	*ft_strfind(char *input, int w_count)
{
	char	*ret;
	int		i;

	i = 0;
	while (w_count > 1 && *input)
	{
		if (*input == ' ')
			w_count--;
		input++;
	}
	while (input[i] != ' ' && input[i])
		i++;
	ret = (char *)ft_memalloc(sizeof(char) * i);
	i = 0;
	while ((ret[i] = *input))
	{
		if (*(input + 1) == ' ' || *(input + 1) == '\0')
			return (ret);
		i++;
		input++;
	}
	return (NULL);
}

void	create_database(char *line, t_apple *apple)
{
	apple->db_name = ft_strfind(line, 3);
	printf("db_name = %s\n", apple->db_name);
}

int		parse_col_type(char *type)
{
	if (ft_strncmp(type, "VARCHAR", 7) == 0)
		return (1);
	return (-1);
}

int		parse_col_length(char *type)
{
	int		ret;

	ret = 0;
	while (*(type - 1) != '(' && *type)
		type++;
	while (*type != ')' && *type)
	{
		ret *= 10;
		ret += *type - '0';
		type++;
	}
	return ((*type == ')' || *type == '\0') && ret != 0) ? (ret) : (-1);
}

int		parse_columns(char **line, t_table *table)
{
	(*line) += 2;
	printf("line: %s\n", (*line));
	table->column_type = ft_realloc_int(table->column_type, table->column_count);
	table->column_length = ft_realloc_int(table->column_length, table->column_count);
	table->columns[table->column_count] = ft_strfind(*(line), 1);
	table->column_length[table->column_count] = parse_col_length(ft_strfind(*(line), 2));
	table->column_type[table->column_count] = parse_col_type(ft_strfind(*line, 2));
	table->column_count++;
	printf("col name = %s\n", table->columns[table->column_count - 1]);
	printf("type = %d\n", table->column_type[table->column_count - 1]);
	printf("length = %d\n", table->column_length[table->column_count - 1]);
	printf("col count = %d\n", table->column_count);
	while (*(*line))
	{
		if (*(*line) == ',')
			return (1);
		(*line)++;
	}
	return (0);
}

void	create_table(char *line, t_table *table)
{
	table->column_count = 0;
	table->name = ft_strfind(line, 3);
	table->columns = (char **)ft_memalloc(sizeof(char *));
	table->columns[0] = (char *)ft_memalloc(sizeof(char));
	printf("table_name = %s\n", table->name);
	while (*line != '(')
		line++;
	while (parse_columns(&line, table) == 1)
		table->columns = ft_dbrealloc_chr(table->columns, table->column_count);
}

void	create_query(char *line, t_apple *apple)
{
	if (ft_strequ(ft_strfind(line, 2), "database"))
		create_database(line, apple);
	else if (ft_strequ(ft_strfind(line, 2), "table"))
	{
		apple->table = (t_table *)ft_memalloc(sizeof(t_table));
		create_table(line, apple->table);
		ft_printf("\n%s table created\n", apple->table->name);
	}
}

void	insert_query(char *line)
{
	line = NULL;
	write(0, "insert\n", 7);

}

void	delete_query(char *line)
{
	line = NULL;
	write(0, "delete\n", 8);

}
void	select_query(char *line)
{
	line = NULL;
	write(0, "select\n", 7);

}

void	read_input(t_apple *apple)
{
	char	*line;

	while (get_next_line(0, &line) == 1)
	{
		if (ft_strequ(ft_strfind(line, 1), "create"))
			create_query(line, apple);
		else if (ft_strequ(ft_strfind(line, 1), "insert"))
			insert_query(line);
		else if (ft_strequ(ft_strfind(line, 1), "delete"))
			delete_query(line);
		else if (ft_strequ(ft_strfind(line, 1), "select"))
			select_query(line);
	}
}

int		main()
{
	t_apple	*apple;

	apple = (t_apple *)ft_memalloc(sizeof(apple));
	read_input(apple);
}
