/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssmith <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:00:25 by ssmith            #+#    #+#             */
/*   Updated: 2017/04/27 14:16:25 by ssmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BLANK(ws) (ws=='\t'||ws=='\v'||ws=='\n'||ws=='\f'||ws=='\r'||ws==' ')
# define BUFF_SIZE 500

# define WHITE    "\x1b[37m"
# define RED      "\x1b[31m"
# define GREEN    "\x1b[32m"
# define YELLOW   "\x1b[33m"
# define BLUE     "\x1b[34m"
# define MAGENTA  "\x1b[35m"
# define GREY     "\x1b[2m"
# define BLACK    "\x1b[90m"
# define BG_GREY  "\x1b[100m"
# define BG_BLACK "\x1b[40m"
# define RESET    "\x1b[0m"

# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <wchar.h>
# include <dirent.h>
# include <stdio.h>
# include <ftw.h>

typedef struct		s_table
{
	char			*name;
	int				column_count;
	char			**columns;
	int				*column_type;
	int				*column_length;
}					t_table;

typedef struct		s_apple
{
	char			*db_name;
	t_table			*table;
}					t_apple;

typedef struct		s_gnl
{
	int				r;
	int				newline;
	int				buffnl;
	int				buffsize;
	char			*buffsave;
}					t_gnl;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_algo {
	char			*in;
	char			flag;
	char			flagh;
	int				flagm;
	int				width;
	int				precision;
	char			*length;
	int				spaces;
	char			spec;
	char			*arg_str;
	int				null_terminator;
	int				in_i;
	char			*out_str;
	va_list			ap;
}					t_algo;

char				*ft_strcstr(const char *s, int c, int c2);
int					*ft_realloc_int(int *ptr, size_t size);
int					*ft_intrealloc(int *arr, size_t size);
int					**ft_dbrealloc(int **ptr, size_t size, size_t size2);
char				**ft_dbrealloc_chr(char **ptr, size_t size);
int					get_next_line(int fd, char **line);
int					ft_strisdigit(char *str, int type);
char				*ft_padend(char *str, int size);
char				*ft_pad(char *str, int size);
void				revdebuff(t_algo *algo);
int					debuff(t_algo *algo);
char				*ft_strlower(char *str);
char				*ft_strupper(char *str);
void				arg_octal(t_algo *algo);
void				arg_hex(t_algo *algo);
void				arg_nbr(t_algo *algo);
void				adjuster(t_algo *algo);
void				arg_int(t_algo *algo, long long d);
void				asterisk(t_algo *algo, int type);
char				*prechrcat(char *s1, char *s2, int precision);
void				ft_strbeg(char *s1, char *s2);
void				arg_char(t_algo *algo);
void				arg_str(t_algo *algo);
void				find_spec(t_algo *algo);
void				find_length(t_algo *algo);
void				find_flag(t_algo *algo);
void				find_width(t_algo *algo);
void				run_spec(t_algo *algo);
void				run_width(t_algo *algo);
void				run_flag(t_algo *algo);
void				flipflag(t_algo *algo);
char				*ft_strrcat(char *s1, const char *s2, size_t size);
int					ft_findnchr(const char *s, int c, int start, int end);
char				*ft_strwcat(char *s1, const wchar_t wc);
int					ft_printf(const char *fmt, ...);
char				*ft_itoau(size_t n);
char				*ft_chrcat(char *s1, const char c);
int					ft_strwhite(char *str);
char				*ft_itoa_basel(unsigned long long value, long base);
char				*ft_itoa_base(int value, int base);
void				ft_delendchr(char *s1);
int					ft_findchr(const char *s, int c);
int					ft_strisalpha(char *str);
char				ft_lastchr(const char *str);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstnew(void const *content, size_t content_size);
int					ft_atoi(const char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				ft_bzero(void *s, size_t n);
char				*ft_chrrealloc(char *str, size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strnstr(const char *b, const char *l, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
char				*ft_itoal(long long n);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int c);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

#endif
