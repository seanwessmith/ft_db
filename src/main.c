//FT_DB

#include "libft.h"
#include <sys/stat.h>
#include <sys/types.h>

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

void	create_database(char *line, t_apple *apple)
{
    apple->db_name = ft_strfind(line, 3);
	mkdir(apple->db_name, 0744);
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
	if (access(ft_strfind(line, 3), F_OK) != -1)
	{
		ft_strfind(line, 3);
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
	else
		printf("The %s table already exists.\n", ft_strfind(line, 3));
}

int	check_table(char *line,t_apple *apple)
{
	char *table;

	table = ft_strnew(ft_strlen(apple->db_name) + ft_strlen(ft_strfind(line, 3) + 2));
	table = ft_strjoin(apple->db_name, "/");
	table = ft_strjoin(table, ft_strfind(line, 3));


	if (access(table, F_OK) != -1)
		return (1);
	else
		return (-1);
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
	else if (ft_strequ(ft_strfind(line, 3), apple->db_name))
	{
		if (nftw(apple->db_name, rmFiles, 10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) < 0)
			printf("FACK the shit wasn't delorted!\n");
		else
			printf("Deleted yer shit, boss!\n");
	}
	else
		printf("Not a database\n");
}

void	create_query(char *line, t_apple *apple)
{
	printf("db_name %s\n", apple->db_name);
	if (ft_strequ(ft_strfind(line, 2), "database"))
		create_database(line, apple);
	else if (ft_strequ(ft_strfind(line, 2), "table") && apple->db_name != NULL)
	{
		apple->table = (t_table *)ft_memalloc(sizeof(t_table));
		create_table(line, apple->table);
		ft_printf("\n%s table created\n", apple->table->name);
	}
	else if (ft_strequ(ft_strfind(line, 2), "table"))
		ft_printf("The table \"%s\" was not created. Must be inside a database first.\n", ft_strfind(line, 3));
}

void	insert_query(char *line)
{
	line = NULL;
	write(0, "insert\n", 7);

}

void	delete_query(char *line, t_apple *apple)
{
	(void)line;
	(void)apple;
}

void	drop_query(char *line, t_apple *apple)
{
	if (line && ft_strequ(ft_strfind(line, 2), "table"))
	{
		if (!apple->db_name)
			printf("No db selected\n");
		else
		{
			if (check_table(line, apple))
				drop_table(line, apple);
			else
				printf("Table not found\n");
		}
	}
	else if (line && ft_strequ(ft_strfind(line, 2), "database"))
		drop_database(line, apple);
}

void	select_query(char *line)
{
    line = NULL;
	write(0, "select\n", 7);

}

void	enter_database(char *line, t_apple *apple)
{
    DIR     *dir;

    if (ft_strequ(ft_strfind(line, 2), "database")
            || ft_strequ(ft_strfind(line, 2), "db"))
    {
        dir = opendir(ft_strfind(line, 3));
        if (dir)
        {
            apple->db_name = ft_strfind(line, 3);
            closedir(dir);
            ft_printf("You have entered into database %s.\n", apple->db_name);
        }
        else
            ft_printf("The %s database does not exist.\n", ft_strfind(line, 3));
    }
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
			delete_query(line, apple);
		else if (ft_strequ(ft_strfind(line, 1), "drop"))
			drop_query(line, apple);
		else if (ft_strequ(ft_strfind(line, 1), "select"))
			select_query(line);
		else if (ft_strequ(ft_strfind(line, 1), "enter") || ft_strequ(ft_strfind(line, 1), "cd"))
			enter_database(line, apple);
		else if (ft_strequ(ft_strfind(line, 1), "exit"))
		{
			printf("Thank you for using STDB\n");
			exit(1);
    }
	}
}

int		main()
{
	t_apple	*apple;
	
	apple = (t_apple *)ft_memalloc(sizeof(apple));
	read_input(apple);
}
