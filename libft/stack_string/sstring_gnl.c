#include "stack_string.h"

/**
 * @brief Read in sstring
 * @param sstr Pointer on the stack string to read in
 * @param fd File descriptor
 * @return 1 if success, else 0
 */
static u8 sstring_read(t_sstring *sstr, int fd)
{
	int     read_result = 1;

	*sstr = empty_sstring();
	if (fd < 0 || !sstr)
		return (0);
	read_result = read(fd, sstr->data, SSTRING_MAX - 1);
	if (read_result <= 0) {
		return (0);
	}
	sstr->size = read_result;
	return (1);
}

char **sstring_load_file(char *path)
{
	t_sstring	line;
	u8			ret_read = 1;
	char		*map = NULL, **dest = NULL;
	int 		fd = -1;	
	
	fd = open(path, O_RDONLY);
	if (fd < 0) {
		ft_printf_fd(2, "Error\nfd incorect \n");
		return (NULL);
	}
	clear_sstring(&line);
	map = ft_strdup("");
	while (ret_read) {
		ret_read = sstring_read(&line, fd);
		map = ft_strjoin_free(map, line.data, 'f');
		clear_sstring(&line);	
		if (ret_read == 0){
			break ;
		}
		// ft_printf_fd(1, ORANGE"map|%s|"RESET,map);
	}

	// ft_printf_fd(1, YELLOW"In sstring load File %s:"RESET"\n"PINK"|%s|"RESET,path,map);
	close(fd);
	dest = ft_split_trim(map, '\n');
	free(map);
	return (dest);
}

void adapt_free(char *s1, char *s2, char option) {
	if (option == 'f' || option == 'a')
		free(s1);
	if (option == 's' || option == 'a')
		free(s2);
}

char *strjoin_free_size(char *s1, char *s2, char option, u64 s1_size, u64 s2_size)
{
	char            *new_s = NULL;
	u64             new_len = s1_size + s2_size, i = 0, j= 0;

	if (!(new_s = malloc((new_len + 1) * sizeof(char)))) {
		adapt_free(s1, s2, option);
		return (NULL);
	}
	while (i < s1_size) {
		new_s[i] = s1[i];
		i++;
	}
	while (i < new_len) {
		new_s[i++] = s2[j++];
	}
	adapt_free(s1, s2, option);
	new_s[i] = '\0';
	return (new_s);
}


/**
 * @brief Read in sstring
 * @param fd File descriptor
 * @param path File path
 * @param size Size of the file
 * @return allocated char*, the fd content
*/
char *sstring_read_fd(int fd, char *path, u64 *size)
{
	t_sstring	buff;
	u8			ret_read = 1;
	char		*file_content = NULL;

	if (fd == -1) {
		fd = open(path, O_RDONLY);
		if (fd < 0) {
			// ft_printf_fd(2, "Error: %s No such file or directory\n", path);
			return (NULL);
		}
	}	
	clear_sstring(&buff);
	file_content = ft_strdup("");
	while (ret_read) {
		ret_read = sstring_read(&buff, fd);
		file_content = strjoin_free_size(file_content, buff.data, 'f', *size, buff.size);
		*size += buff.size;
		clear_sstring(&buff);	
		if (ret_read == 0){
			break ;
		}
	}
	close(fd);
	return (file_content);
}