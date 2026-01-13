#include "../libft.h"

static void     free_str_join(char *s1, char *s2, char option)
{
    if (option == 'f' || option == 'a')
            free(s1);
    if (option == 's' || option == 'a')
            free(s2);
}

char    *ft_strjoin_free(char *s1, char *s2, char option)
{
    int             len_new_s;
    char            *new_s;
    int             i;
    int             j;

    len_new_s = ft_strlen(s1) + ft_strlen(s2);
    new_s = malloc((len_new_s + 1) * sizeof(char));
    if (!new_s)
    {
            free_str_join(s1, s2, option);
            return (NULL);
    }
    i = 0;
    while (s1 && s1[i])
    {
            new_s[i] = s1[i];
            i++;
    }
    j = 0;
    while (s2 && s2[j] && i < len_new_s)
            new_s[i++] = s2[j++];
    free_str_join(s1, s2, option);
    new_s[i] = '\0';
    return (new_s);
}