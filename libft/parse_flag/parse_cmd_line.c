# include "parse_flag.h"

/**
 * @brief Extract file from command line
 * @param argc number of arguments
 * @param argv arguments
 * @return list of files
 */
t_list *extract_args(int argc, char **argv)
{
	t_list *lst = NULL;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '\0') {
			ft_lstadd_back(&lst, ft_lstnew(ft_strdup(argv[i])));
		}
	}
	return (lst);
}