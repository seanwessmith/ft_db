/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:58:37 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 19:46:15 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "db.h"

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
	DIR		*dir = opendir(ft_strfind(line, 3));
	if (dir)
		printf("A database already exists with the name %s.\n", ft_strfind(line, 3));
	else
	{
    	apple->db_name = ft_strfind(line, 3);
		mkdir(apple->db_name, 0744);
		ft_printf("You successfully created the %s database.\n", apple->db_name);
	}
}

int     parse_col_type(char *type)
{
	if (ft_strncmp(type, "VARCHAR", 7) == 0)
		return (1);
	if (ft_strncmp(type, "int", 3) == 0)
		return (2);
	else
		printf("Column type %s is invalid.", ft_strcstr(type, '(', ','));
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
	table->column_type = ft_realloc_int(table->column_type, table->column_count);
	table->column_length = ft_realloc_int(table->column_length, table->column_count);
	table->columns[table->column_count] = ft_strfind(*(line), 1);
	table->column_length[table->column_count] = parse_col_length(ft_strfind(*(line), 2));
	if ((table->column_type[table->column_count] = parse_col_type(ft_strfind(*line, 2))) == -1)
		return (-1);
	table->column_count++;
	while (*(*line))
	{
		if (*(*line) == ',')
		{
			(*line)++;
			return (1);
		}
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
        printf("The %s table was successfully created.\n", table->name);
    else
        printf("There was an error creating the %s table.\n", table->name);
}

void    create_table(t_apple *apple)
{
    char    *create_file;
    int     fd;

    create_file = ft_strnew(0);
	create_file = ft_strjoin(apple->db_name, "/");
    create_file = ft_strjoin(create_file, apple->table->name);
    if (access(create_file, F_OK) != -1)
		printf("A table already exists with the name %s.\n", apple->table->name);
	else if (apple->table->column_count == 0)
		printf("Invalid table format. Needs at least 1 column.\n");
	else
	{
		fd = open(create_file, O_CREAT | O_WRONLY, 0744);
    	write_to_table(apple->table, fd);
    	close(fd);
	}
}

int 	parse_table(char *line, t_table *table)
{
	int		ret;

	ret = 0;
	if (access(ft_strfind(line, 3), F_OK) == -1)
	{
		ft_strfind(line, 3);
		table->column_count = 0;
		table->name = ft_strcstr(ft_strfind(line, 3), '\0', '(');
		table->columns = (char **)ft_memalloc(sizeof(char *));
		table->columns[0] = (char *)ft_memalloc(sizeof(char));
		while (*line && *line != '(')
			line++;
		line++;
		while (*line && (ret = parse_columns(&line, table)) == 1)
			table->columns = ft_dbrealloc_chr(table->columns, table->column_count);
		if (ret == -1)
			return (-1);
		return (1);
    }
    return (-1);
}

void	create_query(char *line, t_apple *apple)
{
	int		ret;

	ret = 0;
	if (ft_strequ(ft_strupper(ft_strfind(line, 2)), "DATABASE"))
		create_database(line, apple);
	else if (ft_strequ(ft_strupper(ft_strfind(line, 2)), "TABLE") && apple->db_name != NULL)
	{
		apple->table = (t_table *)ft_memalloc(sizeof(t_table));
		if ((ret = parse_table(line, apple->table)) == 1)
			create_table(apple);
		else
			printf("The %s table was not created.\n", ft_strfind(line, 3));
	}
	else if (ft_strequ(ft_strupper(ft_strfind(line, 2)), "TABLE"))
		ft_printf("The table \"%s\" was not created. Must be inside a database first.\n", ft_strfind(line, 3));
}

char	*next_word(char *line)
{
	while (*line == ' ' || *line == ',' || *line == '\"')
		line++;
	return (line);
}

char	*end_string(char *line)
{
	int		quotes;

	quotes = 0;
	while (*line && quotes != 2)
	{
		if (*line == '\"')
			quotes++;
		line++;
	}
	if (*(line - 1) == '\"')
		return (line);
	return (NULL);
}

char	*end_int(char *line)
{
	while (*line && *line != ',')
		line++;
	if (*line == ',')
	{
		line++;
		return (line);
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

void	enter_database(char *line, t_apple *apple)
{
	DIR     *dir;

	if (ft_strequ(ft_strupper(ft_strfind(line, 2)), "DATABASE")
			|| ft_strequ(ft_strupper(ft_strfind(line, 2)), "DB"))
	{
		dir = opendir(ft_strfind(line, 3));
		if (dir)
		{
			apple->db_name = ft_strfind(line, 3);
			closedir(dir);
			printf("You have entered into database %s.\n", apple->db_name);
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
		if (ft_strequ(ft_strupper(ft_strfind(line, 1)), "CREATE"))
			create_query(line, apple);
		if (ft_strequ(ft_strupper(ft_strfind(line, 1)), "INSERT"))
			insert_query(line, apple);
		if (ft_strequ(ft_strupper(ft_strfind(line, 1)), "DELETE"))
			delete_query(line);
		if (ft_strequ(ft_strupper(ft_strfind(line, 1)), "DROP"))
			drop_query(line, apple);
		if (ft_strequ(ft_strupper(ft_strfind(line, 1)), "SELECT"))
			select_query(line, apple);
		if (ft_strequ(ft_strupper(ft_strfind(line, 1)), "ENTER") ||
				ft_strequ(ft_strupper(ft_strfind(line, 1)), "CD"))
			enter_database(line, apple);
		if (ft_strequ(ft_strupper(line), "EXIT"))
		{
			printf("Thank you for using STDB\n");
			exit(1);
    	}
    	prev = ft_strnew(ft_strlen(line) + 1);
    	prev = line;
	}
}

int		main()
{
	t_apple	*apple;
	
	apple = (t_apple *)ft_memalloc(sizeof(apple));
	read_input(apple);
}
