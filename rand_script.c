#include "libft/includes/libft.h"
#include <stdio.h>

char	*itoalpha(int nbr)
{
	int		i = 0;
	char	*str;

	str = (char *)ft_memalloc(sizeof(char) * ft_nbrlen(nbr));
	str[i++] = nbr % 10 + 65;
	nbr /= 10;
	while ((nbr /= 10) > 0)
	{
		str[i] = nbr % 10 + 97;
		i++;
	}
	return (str);
}

char	*itoalpha_lower(int nbr)
{
	int		i = 0;
	char	*str;

	str = (char *)ft_memalloc(sizeof(char) * ft_nbrlen(nbr));
	while ((nbr /= 10) > 0)
	{
		str[i] = nbr % 10 + 97;
		i++;
	}
	return (str);
}

int		main(int ac, char **av)
{
	int		i;
	int		fd;
	int		nbr;
	char	*str;

	if (ac > 1)
	{
		i = ft_atoi(av[1]);
		fd = open("output.txt", O_CREAT | O_WRONLY, 0744);
		str = ft_strdup("INSERT INTO users (1, \"taramann\", \"Tara Mann\")");
		while (--i >= 0)
		{
			str = ft_strjoin(str, ", (");
			str = ft_strjoin(str, ft_itoa(ft_randint(1)));
			str = ft_strjoin(str, ", \"@");
			nbr = ft_randint(5);
			str = ft_strjoin(str, itoalpha_lower(ft_randint(5)));
			str = ft_strjoin(str, "\", \"");
			nbr = ft_randint(5);
			str = ft_strjoin(str, itoalpha(ft_randint(5)));
			str = ft_strjoin(str, " ");
			nbr = ft_randint(5);
			str = ft_strjoin(str, itoalpha(ft_randint(5)));
			str = ft_strjoin(str, "\")");
		}
		write(fd, str, ft_strlen(str));
		close(fd);
		printf("File complete\n");
	}
}
