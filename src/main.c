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

void	create_query(char *line, t_db *db)
{
	if (ft_strequ(ft_strfind(line, 2), "database"))
		create_database(line, db);
	else if (ft_strequ(ft_strfind(line, 2), "table"))
		create_table(line, db);
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

void	read_input(t_db *db)
{
	char	*line;

	db = NULL;
	while (get_next_line(0, &line) == 1)
	{
		if (ft_strequ(ft_strfind(line, 1), "create"))
			create_query(line, db);
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
	t_db	*db;

	db = (t_db *)ft_memalloc(sizeof(db));
	read_input(db);
}
