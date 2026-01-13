#include "../basic_define.h"

s32 count_char(char *str, char c) {
	s32 nb = 0, i = 0;
	while (str && str[i]) {
		if (str[i] == c) {
			nb++;
		}
		i++;
	}
	return (nb);
}

s8 is_space(char c) {
	return ((c >= '\b' && c <= '\r') || c == ' ');
}