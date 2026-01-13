#include "../libft.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static int	ft_in_set(char c, char set)
{
	if (c == set)
		return (1);
	return (0);
}

static char	**ft_make_split(char **dest, char const *str, char c, int j)
{
	size_t	len = 0;
	int		i = 0;

	while (str[i]) {
		if (ft_in_set(str[i], c) == 1) {
			i++;
		}
		else {
			len++;
			i++;
			if (str[i] == c || (str[i] == '\0' && j < ft_count_word(str, c))) {
				dest[j] = ft_calloc(sizeof(char), len + 1);
				ft_strlcpy(dest[j], &str[i - len], len + 1);
				len = 0;
				char *trim_path = ft_strtrim(dest[j], "\b\t\n\v\f\r ");
				free(dest[j]);
				dest[j] = trim_path;
				j++;
			}
		}
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split_trim(char const *str, char c)
{
	char	**dest;
	int		j;
	int		nb_word;

	if (str == NULL) {
		return (NULL);
	}
	nb_word = ft_count_word(str, c);
	j = 0;
	dest = malloc(sizeof(char *) * (nb_word + 1));
	if (dest == NULL){
		return (NULL);
	}
	dest = ft_make_split(dest, str, c, j);
	return (dest);
}