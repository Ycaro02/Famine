#ifndef STACK_STRING_H
#define STACK_STRING_H

#include "../libft.h"

/**
 * Basic stack string implementation, using a fixed size buffer
 * This is useful for small strings, and avoid dynamic allocation
 * Written by Ycaro
*/


/**
 * @brief Create an empty stack string
*/
t_sstring   empty_sstring();

/**
 * @brief Fill a stack string with a string
 * @param str The string to fill the stack string with
*/
t_sstring   fill_sstring(char *str);

/**
 * @brief Fill a stack string with multiple strings
 * @param str1 The first string to fill the stack string with
 * @param str2 The second string to fill the stack string with
 * @param str3 The third string to fill the stack string with
*/

t_sstring   fill_multiple_sstring(char *str1, char *str2, char *str3);

/**
 * @brief Clear a stack string
 * @param sstr Pointer on the stack string to clear
*/
void        clear_sstring(t_sstring *sstr);

/**
 * @brief Push a char in a stack string
 * @param sstr Pointer on the stack string to push the char in
*/
void        push_sstring(t_sstring *sstr, char c);

/**
 * @brief Pop a char from a stack string
 * @param sstr Pointer on the stack string to pop the char from
*/
void		pop_sstring(t_sstring *sstr);

/**
 * @brief Concatenate a string to a stack string
 * @param sstr Pointer on the stack string to concatenate the string to
 * @param str The string to concatenate
*/
void        concat_sstring(t_sstring *sstr, char *str);

/**
 * @brief Load a file using stack string for read
 * @param path The path to the file to load
 * @return A double allocated char array 
 * containing the file content with each line as a string and without newline character
*/
char **sstring_load_file(char *path);

char *sstring_read_fd(int fd, char *path, u64 *size);

#endif /* STACK_STRING_H */