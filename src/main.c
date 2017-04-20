//FT_DB

#include "libft.h"

int		main(int ac, char **av)
{
	char	*line;

	ac = 0;
	av = NULL;
	while (get_next_line(0, &line) == 1)
		printf("line: %s", line);
}
