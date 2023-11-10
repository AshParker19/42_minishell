/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:11:36 by astein            #+#    #+#             */
/*   Updated: 2023/11/10 17:42:06 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//******************************************************************************
// BUFFER SIZE FOR GET NEXT LINE
//******************************************************************************
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# define GNL_INTERRUPTED -111

//******************************************************************************
// PARAMS FOR print_header.c
//******************************************************************************
# define HEADER_SEP 45
# define HEADER_WIDTH 51

//******************************************************************************
// Hexadecimal Value Definitions
//******************************************************************************
# define HEXA_LOWER "0123456789abcdef"
# define HEXA_UPPER "0123456789ABCDEF"

//******************************************************************************
//			DEFINE TEMINAL COLOR
//******************************************************************************
# define WRITE_COLOR_DEFAULT "\033[0m"
# define WRITE_COLOR_RED "\033[31m"
# define WRITE_COLOR_GREEN "\033[32m"
# define WRITE_COLOR_ORANGE "\033[33m"

//******************************************************************************
//			Typedefs
//******************************************************************************

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef enum e_bool
{
	ft_false = 0,
	ft_true = 1
}					t_bool;

typedef enum e_dbg_flag
{
	err_block = -1,
	no_block = 0,
	start_block = 1,
	end_block = 2,
	success_block = 3,
	no_lb_block = 4
}					t_dbg_flag;

//******************************************************************************
//			ft_printf
//******************************************************************************
int					ft_printf(const char *str, ...);
void				dbg_printf(t_dbg_flag dbg_flg, char *str, ...);
int					print_whatever(va_list args, char *str);
int					print_whatever_digits(va_list args, char *str);

//******************************************************************************
//			Other print functions
//******************************************************************************
void				print_char(char c, int *len);
void				print_str(char *str, int *len);
void				print_dez_to_hexa(unsigned long dez_nbr, int *len,
						t_bool caps);
void				print_ptr(unsigned long ptr, int *len);
void				print_nbr(long nbr, int *len);

//******************************************************************************
//			Output Functions
//******************************************************************************
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				put_header(char *symbol, char *msg);
void				put_exit_header(int exit_status, char *msg);

//******************************************************************************
//			Character Classification Functions
//******************************************************************************
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

//******************************************************************************
//			String Functions
//******************************************************************************
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strcat_multi(int amount_of_strs, ...);
char 				*append_str(char *cur_str, char *add_str, t_bool free_add_str);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_bool				str_cmp_strct(const char *str_a, const char *str_b);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
void				ft_str_replace_chr(char *str, char old, char new);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_chr2str(char c);
void    			ft_swap_strings(char **a, char **b);
t_bool				ft_str_is_numeric(char *str);


//******************************************************************************
//			Memory Functions
//******************************************************************************
void				*ft_calloc(size_t nmemb, size_t size);
void				*free_whatever(char *str, ...);
void				ft_bzero(void *s, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);

//******************************************************************************
//			Conversion Functions
//******************************************************************************
int					ft_atoi(const char *nptr);
char				*ft_itoa(int n);
char				*ft_dtoa(double d, unsigned int digits);
char				*ft_btoa(t_bool b, int flg);
char				**ft_split(char const *s, char c);

//******************************************************************************
//			Linked List Functions
//******************************************************************************
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				null_ptr(void *nothing);
void				free_content(void *node);
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

//******************************************************************************
//			gnl.c
//******************************************************************************
char				*gnl(int fd);
char				*gnl_stoppable(int fd, t_bool stop);
void				*gnl_zero_str(char *str);
void				gnl_len_nl(char *str, size_t *len, t_bool *flg_nl);
char				*gnl_safe_buffer(char *line, size_t len_line, char *buffer, size_t len_cpy);
void				gnl_shift_arr_to_front(char *arr, size_t offset);

#endif
