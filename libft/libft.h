/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:43:41 by nfour             #+#    #+#             */
/*   Updated: 2025/01/31 14:51:27 by nfour            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stdlib.h>
#include <unistd.h>
#include "limits.h"
#include <fcntl.h>
#include <errno.h>

#include "basic_define.h"
#include "list/linked_list.h"
#include "bitshift_utils.h"

/* Buffer size of stack string */
#define SSTRING_MAX 1024

#define OUT_OF_SSTRING 1025

/**
 * Stack string structure
*/
typedef struct s_stack_string
{
    char        data[SSTRING_MAX];      /* char buffer */
    u16    size;                   /* Current len of string, position of \0 */
}	t_stack_string;

typedef t_stack_string t_sstring;




#define BUFFER_SIZE 1
#define OUT_OF_UINT32 (u64)(UINT32_MAX + 1ULL)

/* Libft */
char    *get_next_line(int fd); /* Get next line */
char    *ft_strjoin_gnl(char *s1, char *s2);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *det, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *str, char c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int 	ftlib_strcpy(char* dst, char *src, int len);	
void 	ft_free_tab(char **tab);
char    *ft_strjoin_free(char *s1, char *s2, char option);
int 	ft_lower_strcmp(char *s1, char *s2);
int 	ftlib_strcmp(char *s1, char *s2);
void 	free_incomplete_array(void **array, int max);
s8	    str_is_digit(char *str);
s8	    str_is_hexa(char *str);
s8      str_is_octal(char *str);
s8      str_is_binary(char *str);
int		ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*str_tolower(char *str);

s32 count_char(char *str, char c);
s8 is_space(char c);

int		fast_strcmp(const char *s1, const char *s2);
int		fast_strlen(const char *s);
char	*fast_strcpy(char *dst, const char *src);
void	fast_bzero(void *s, size_t n);

/* Double char array handling */

/**
 * @brief Free a double char array
 * @param char **array to free
*/
void	free_double_char(char **array);

/**
 * @brief Display a double char array
 * @param char **array to display
*/
void	display_double_char(char **array);

/**
 * @brief Get double char size
 * @param char **array to count
 * @return array len
*/
u32		double_char_size(char **array);

/**
 * @brief Split a string and remove the leading and trailing whitespaces
 * @param str string to split
 * @param c character to split the string
 * @return array of string
*/
char	**ft_split_trim(char const *str, char c);


/*-+-+-+-+-+-+-+-+-+-+-+-+-+*/
/*-+-+ String to number +-+*/
/*-+-+-+-+-+-+-+-+-+-+-+-+-+*/

/**
 * @brief Check if a string is a float
 * @param str string to check
 * @return 1 if the string is a float, 0 otherwise
*/
u8		str_is_float(char *str);

/**
 * @brief Convert a string to a float
 * @param str string to convert
 * @return float
*/
float	ft_atof(char *str);

/**
 *  @brief Convert a string to a uint32
 *	@param nptr string to convert
 *	@return uint32
*/
u64 array_to_uint32(const char *nptr);

/**
 * @brief Convert a string to a int
 * @param str string to convert
 * @return int
*/
int		ft_atoi(const char *str);

/*-+-+-+-+-+-+-+-+-+-+-+-+-+*/
/*-+-+ Number to string +-+*/
/*-+-+-+-+-+-+-+-+-+-+-+-+-+*/

/**
 * @brief Convert int to an array
 * @param n number to convert\
 * @return allocated char *
*/
char	*ft_itoa(int n);

/**
 * @brief Convert long int to an array
 * @param n number to convert\
 * @return allocated char *
*/
char	*ft_ltoa(long n);

/**
 *	@brief Convert unsigned long to string
 *	@param n unsigned long value
 *	@return allocated char *
*/
char	*ft_ultoa(unsigned long n);


/**
 * @brief Check if the size of a struct is the same as the wanted size
 * @param str_test name of the struct
 * @param struct_size size of the struct
 * @param wanted_size wanted size of the struct
*/
void check_struct_size(char *str_test, u32 struct_size, u32 wanted_size);

/* Math */

/**
 * @brief Return the absolute value between uint32 a and b 
*/
u32 abs_diff(u32 a, u32 b);

/**
 * @brief Return the maximum value between uint32 a and b
*/
u32 max_uint32(u32 a, u32 b);

/**
 * @brief Return the minimum value between uint32 a and b
*/
u32 min_uint32(u32 a, u32 b);


/* Use ft_memcpy in mat4 */
#include "math/ft_math.h"

/* Use some libft function */
#include "stack_string/stack_string.h"

#include "printf_fd/ft_printf.h"

#endif
