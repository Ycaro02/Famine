#include "stack_string.h"

t_sstring empty_sstring()
{
    t_sstring str;

    ft_bzero(&str, sizeof(t_sstring));
    return (str);
}

t_sstring fill_sstring(char *str)
{
    t_sstring sstr;
    size_t len = ft_strlen(str);

    ft_bzero(&sstr, sizeof(t_sstring));
    ftlib_strcpy(sstr.data, str, len);
    sstr.size = len;
    return (sstr);
}

t_sstring fill_multiple_sstring(char *str1, char *str2, char *str3)
{
    t_sstring sstr;

    sstr = fill_sstring(str1);
    concat_sstring(&sstr, str2);
    concat_sstring(&sstr, str3);
    return (sstr);
}


void clear_sstring(t_sstring *sstr) {
    ft_bzero(sstr, sizeof(t_sstring));
}

void push_sstring(t_sstring *sstr, char c)
{
    if (sstr->size < SSTRING_MAX) {
        sstr->data[sstr->size] = c;
        sstr->size += 1;
        sstr->data[sstr->size] = 0;
    }
}

void concat_sstring(t_sstring *sstr, char *str)
{
    size_t len = ft_strlen(str);

    if (sstr->size + len < SSTRING_MAX) {
        ftlib_strcpy(sstr->data + sstr->size, str, len);
        sstr->size += len;
        sstr->data[sstr->size] = 0;
    }
}

void pop_sstring(t_sstring *sstr)
{
	if (sstr->size > 0) {
		sstr->size -= 1;
		sstr->data[sstr->size] = 0;
	}
}