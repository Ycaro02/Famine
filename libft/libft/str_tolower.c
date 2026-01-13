#include "../libft.h"

char *str_tolower(char *str) {
	char *no_caps = ft_strdup(str);
	u64 len = ft_strlen(str);
	for (u64 i = 0; i < len; i++) {
		if (no_caps[i] >= 'A' && no_caps[i] <= 'Z') {
			no_caps[i] = ft_tolower(str[i]);
		}
	}
	return (no_caps);
}
