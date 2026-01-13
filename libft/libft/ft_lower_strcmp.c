#include "../libft.h"

int ft_lower_strcmp(char *s1, char *s2)
{
    int i = 0;
    char first = '\0';
    char two = '\0';
    while (s1 && s1[i] && s2 && s2[i])
    {
        first = ft_tolower(s1[i]);
        two = ft_tolower(s2[i]);
        if (first != two)
            return (first - two);
        i++;
    }
    if (s1[i] != '\0' || s2[i] != '\0')
        return (s1[i] - s2[i]);
    return (0);
}