/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   droppers_deleters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:39:58 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 19:59:53 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "db.h"

char	*ft_strfind(char *input, int w_count)
{
    char	*ret;
    int		i;

    ret = ft_strnew(0);
	while (*input == ' ')
		input++;
	while (*input && w_count > 1)
	{
		if (*input == ' ')
			w_count--;
		input++;
	}
	i = 0;
	while (input[i] && input[i] != ' ')
		i++;
	ret = (char *)ft_memalloc(sizeof(char) * (i + 1));
	i = 0;
	while (*input && (ret[i] = *input))
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

void	drop_table(char *line, t_apple *apple)
{
	char *table;

	table = ft_strnew(ft_strlen(apple->db_name) + ft_strlen(ft_strfind(line, 3) + 2));
	table = ft_strjoin(apple->db_name, "/");
	table = ft_strjoin(table, ft_strfind(line, 3));

	if (remove(table) == 0)
			printf("The %s table has been deleted.\n", ft_strfind(line, 3));
	else
		printf("Failed to delete the %s table.", ft_strfind(line, 3));
}

void	delete_query(char *line)
{
	line = NULL;
	write(0, "delete\n", 8);

}

void	drop_database(char *line, t_apple *apple)
{
	if (!apple->db_name)
		printf("Error son, no db selected! Fuck!\n");
	else if (ft_strequ(ft_strupper(ft_strfind(line, 3)), apple->db_name))
	{
		if (nftw(apple->db_name, rmFiles, 10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) < 0)
			printf("FACK the shit wasn't delorted!\n");
		else
			printf("Deleted yer shit, boss!\n");
	}
	else
		printf("Not a database\n");
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

void	drop_query(char *line, t_apple *apple)
{
	if (line && ft_strequ(ft_strupper(ft_strfind(line, 2)), "TABLE"))
	{
		if (!apple->db_name)
			printf("No db selected\n");
		else
		{
			if (check_table(ft_strfind(line, 3), apple) == 1)
				drop_table(line, apple);
			else
				printf("The %s table does not exist\n", ft_strfind(line, 3));
		}
	}
	else if (line && ft_strequ(ft_strupper(ft_strfind(line, 2)), "DATABASE"))
		drop_database(line, apple);
	else
		printf("Incorrect query.\n");
}
