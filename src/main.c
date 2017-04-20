//FT_DB

#include "libft.h"

int		q_type(char *q_type, char *input)
{
	while (*q_type)
	{
		if (*q_type != *input)
			return (0);
		input++;
		q_type++;
	}
	return (1);
}

void	create_query(char *line)
{
	line = NULL;
	write(0, "create\n", 7);
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

void	read_input()
{
	char	*line;

	while (get_next_line(0, &line) == 1)
	{
		if (q_type("create", line))
			create_query(line);
		else if (q_type("insert", line))
			insert_query(line);
		else if (q_type("delete", line))
			delete_query(line);
		else if (q_type("select", line))
			select_query(line);
	}
}

int		main()
{
	read_input();
}
