#include "../libft.h"

static s8	is_digit_char(char c) {
	return (c >= 48 && c <= 57);
}

static s8 is_hexadigit_char(char c) {
	return (ft_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}

static s8 is_octal_char(char c) {
	return (c >= '0' && c <= '8');
}

static s8 is_binary_char(char c) {
	return (c == '0' || c == '1');
}

static s8 str_is_anything(char *str, s8 (*cmp_func)(char)) {
	if (!str || !str[0]) {
        return (FALSE);
    }
    for (int i = 0; str[i]; ++i) {
        if (!cmp_func(str[i])) {
            return (FALSE);
        }
    }
    return (TRUE);
}

s8 str_is_digit(char *str)  {
	return (str_is_anything(str, is_digit_char));
}

s8 str_is_hexa(char *str)  {
	return (str_is_anything(str, is_hexadigit_char));
}

s8 str_is_octal(char *str) {
	return (str_is_anything(str, is_octal_char));
}

s8 str_is_binary(char *str) {
	return (str_is_anything(str, is_binary_char));
}