//FT_DB

#include "libft.h"
#include <sys/stat.h>
#include <sys/types.h>

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

int     ft_colfind(char *input, int w_count)
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
        if (*(input + 1) == ',' || *(input + 1) == ')' || *(input + 1) == '\0')
            return (ft_atoi(ret));
        i++;
        input++;
    }
	return (-1);
}

void	create_database(char *line, t_apple *apple)
{
    apple->db_name = ft_strfind(line, 3);
	mkdir(apple->db_name, 0744);
	ft_printf("You successfully created the %s database.\n", apple->db_name);
}

int     parse_col_type(char *type)
{
	if (ft_strncmp(type, "VARCHAR", 7) == 0)
		return (1);
	if (ft_strncmp(type, "int", 3) == 0)
		return (2);
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
	while (*(*line))
	{
		if (*(*line) == ',')
			return (1);
		(*line)++;
	}
	return (0);
}

void    write_to_table(t_table *table, int fd)
{
    char    *s;
    int     i;

    i = 0;
    s = ft_strnew(0);
    s = ft_strjoin(s, "[");
    while (i < table->column_count)
    {
        s = (i > 0) ? ft_strjoin(s, ", (") : ft_strjoin(s, "(");
        s = ft_strjoin(s, table->columns[i]);
        s = ft_strjoin(s, ", ");
        s = ft_strjoin(s, ft_itoa(table->column_type[i]));
        if (table->column_type[i] == 1)
        {
            s = ft_strjoin(s, ", ");
            s = ft_strjoin(s, ft_itoa(table->column_length[i]));
        }
        s = ft_strjoin(s, ")");
        i++;
    }
    s = ft_strjoin(s, "]\n");
    if (write(fd, s, ft_strlen(s)) == (ssize_t)ft_strlen(s))
        ft_printf("The %s table was successfully created.\n", table->name);
    else
        ft_printf("There was an error creating the %s table.\n", table->name);
}

void    create_table(t_apple *apple)
{
    char    *create_file;
    int     fd;

    create_file = ft_strnew(0);
    create_file = ft_strjoin(apple->db_name, "/");
    create_file = ft_strjoin(create_file, apple->table->name);
    fd = open(create_file, O_CREAT | O_WRONLY, 0744);
    write_to_table(apple->table, fd);
    close(fd);
}

int 	parse_table(char *line, t_table *table)
{
	if (access(ft_strfind(line, 3), F_OK) == -1)
	{
		ft_strfind(line, 3);
		table->column_count = 0;
		table->name = ft_strfind(line, 3);
		table->columns = (char **)ft_memalloc(sizeof(char *));
		table->columns[0] = (char *)ft_memalloc(sizeof(char));
		while (*line && *line != '(')
			line++;
		while (*line && parse_columns(&line, table) == 1)
			table->columns = ft_dbrealloc_chr(table->columns, table->column_count);
        return (1);
    }
    return (-1);
}

void	create_query(char *line, t_apple *apple)
{
	if (ft_strequ(ft_strfind(line, 2), "database"))
		create_database(line, apple);
	else if (ft_strequ(ft_strfind(line, 2), "table") && apple->db_name != NULL)
	{
		apple->table = (t_table *)ft_memalloc(sizeof(t_table));
		if (parse_table(line, apple->table) == 1)
            create_table(apple);
        else
            ft_printf("The %s table was not created.\n", ft_strfind(line, 3));
	}
	else if (ft_strequ(ft_strfind(line, 2), "table"))
		ft_printf("The table \"%s\" was not created. Must be inside a database first.\n", ft_strfind(line, 3));
}

int		parse_insert_string(char **ret, char **line, int col, t_table *table)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	*ret = ft_strjoin(*ret, "(");
	while (*(*line - 1) != '\"')
		line++;
	while (*(*line) && *(*line) != '\"' && *(*line) != ')' && i++ <= table->column_length[col])
	{
		*ret = ft_chrcat(*ret, *(*line));
		(*line)++;
	}
	if (i > table->column_length[col])
	{
		ft_printf("String would be truncated. The statement has been terminated\n");
		return (-1);
	}
	*ret = ft_strjoin(*ret, ")");
	return (1);
}

int		parse_insert_int(char **ret, char **line)
{
	int		flag;

	flag = 0;
	*ret = ft_strjoin(*ret, "(");
	while (*(*line) && *(*line) != ',' && *(*line) != ')' && flag == 0)
	{
		if (*(*line) < '0' || *(*line) > '9')
			return (-1);
		else
			*ret = ft_chrcat(*ret, *(*line));
		(*line)++;
	}
	*ret = ft_strjoin(*ret, ")");
	return (1);
}

char	*next_word(char *line)
{
	while (*line == ' ' || *line == ',' || *line == '\"')
		line++;
	return (line);
}

char    *parse_insert_record(char *line, t_table *table)
{
    int     i;
	int		flag;
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
			if (parse_insert_string(&ret, &line, i, table) == -1)
				return (NULL);
		}
		else if (table->column_type[i] == 2)
			if (parse_insert_int(&ret, &line) == -1)
				return (NULL);
		line = next_word(line);
    }
	return (ret);
}

char    *parse_insert(char *line, char *file, t_table *table)
{
	int		fd;
    char    *s;

    while (*line && *line != '(')
        line++;
	line++;
	fd = open(file, O_WRONLY | O_APPEND);
    while (*line)
    {
        if (*line == '(')
        {
			line++;
    		s = ft_strnew(0);
            s = ft_strjoin(s, "[");
            s = ft_strjoin(s, parse_insert_record(line, table));
            s = ft_strjoin(s, "]\n");
			write(fd, s, ft_strlen(s));
        }
        line++;
    }
    return (NULL);
}

void    parse_table_header(char *file, t_table *table)
{
    int     fd;
    char    *line;

    table->column_count = 0;
    fd = open(file, O_RDONLY);
    get_next_line(fd, &line);
    while (*line && *line != ']')
    {
        if (*line == '(')
        {
	        table->column_type = ft_realloc_int(table->column_type, table->column_count);
	        table->column_length = ft_realloc_int(table->column_length, table->column_count);
            table->column_type[table->column_count] = ft_colfind(line, 2);
            if (table->column_type[table->column_count] == 1)
                table->column_length[table->column_count] = ft_colfind(line, 3);
            table->column_count++;
        }
        line++;
    }
}

void	insert_query(char *line, t_apple *apple)
{
    char    *file;

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
            parse_insert(line, file, apple->table);
        }
        else
            ft_printf("The %s table doesn't exist\n", apple->table->name);
    }
    else
        ft_printf("Records were not inserted. Must enter database first\n");
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
			insert_query(line, apple);
		else if (ft_strequ(ft_strfind(line, 1), "delete"))
			delete_query(line);
		else if (ft_strequ(ft_strfind(line, 1), "select"))
			select_query(line);
		else if (ft_strequ(ft_strfind(line, 1), "enter") || ft_strequ(ft_strfind(line, 1), "cd"))
			enter_database(line, apple);
	}
}

int		main()
{
	t_apple	*apple;
	
	apple = (t_apple *)ft_memalloc(sizeof(apple));
	read_input(apple);
}
