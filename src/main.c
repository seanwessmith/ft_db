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
	else if (line && ft_strequ(ft_strfind(line, 2), "database"))
		drop_database(line, apple);
}

int		open_table(char *table, t_apple *apple)
{
	int		fd;
	char	*line;
	char	*path;

	line = NULL;
	fd = 0;
	if (!apple->table)
		printf("No table selected.\n");
	else
	{
		path = ft_strnew(ft_strlen(apple->db_name) + ft_strlen(table) + 2);
		path = ft_strjoin(apple->db_name, "/");
		path = ft_strjoin(path, table);

		fd = open(path, O_RDONLY);
	}
	return (fd);
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

void	select_query(char *line, t_apple *apple)
{
	int i;

	i = 1;

	while (!ft_strequ(ft_strfind(line, i), "from"))
		i++;
	i++;
	if (!apple->db_name)
		printf("No Database selected.\n");
    else if (check_table(ft_strfind(line, i), apple) == 1)
    {
    	if (ft_strequ(ft_strfind(line, 2), "*"))
    		select_all_from_table(ft_strfind(line, i), apple);
    	else
    		select_columns_from_table(line, ft_strfind(line, i), apple);
    }
    else
    {
    	printf("Table not found.\n");
    }
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
	char	*prev;
	int		i;

	prev = NULL;
	while (get_next_line(0, &line) == 1)
	{
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] == '\33')
				if (line[i+2] == 'A')
				{
					printf("%s\n", prev);
					line = prev;
				}
			i++;
		}
		if (ft_strequ(ft_strfind(line, 1), "\027[A"))
			printf("%s\n",line);
		else if (ft_strequ(ft_strfind(line, 1), "create"))
			create_query(line, apple);
		else if (ft_strequ(ft_strfind(line, 1), "insert"))
			insert_query(line);
		else if (ft_strequ(ft_strfind(line, 1), "delete"))
			delete_query(line, apple);
		else if (ft_strequ(ft_strfind(line, 1), "drop"))
			drop_query(line, apple);
		else if (ft_strequ(ft_strfind(line, 1), "select"))
			select_query(line, apple);
		else if (ft_strequ(ft_strfind(line, 1), "enter") || ft_strequ(ft_strfind(line, 1), "cd"))
			enter_database(line, apple);
		else if (ft_strequ(ft_strfind(line, 1), "exit"))
		{
			printf("Thank you for using STDB\n");
			exit(1);
    	}
    	prev = ft_strnew(ft_strlen(line)+ 1);
    	prev = line;
	}
}

int		main()
{
	t_apple	*apple;
	
	apple = (t_apple *)ft_memalloc(sizeof(apple));
	read_input(apple);
}
