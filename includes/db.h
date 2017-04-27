/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:35:04 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 09:51:36 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DB_H
# define DB_H

# include <sys/stat.h>
# include <sys/types.h>

char	*ft_strfind(char *input, int w_count);
void	select_all_from_table(char *table, t_apple *apple);
void	select_columns_from_table(char *line, char *table, t_apple *apple);
void    parse_table_header(char *file, t_table *table);
char    *parse_insert(char *line, char *file, t_table *table);
char    *parse_insert_record(char *line, t_table *table);
char	*next_word(char *line);
int		check_table(char *line, t_apple *apple);
int		open_table(char *table, t_apple *apple);
void	drop_table(char *line, t_apple *apple);
void	drop_database(char *line, t_apple *apple);
void	drop_query(char *line, t_apple *apple);
void	delete_query(char *line);
void	insert_query(char *line, t_apple *apple);
void	select_query(char *line, t_apple *apple);

#endif
