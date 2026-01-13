#include "../libft.h"

void ft_free_tab(char **tab)
{
    int i;

    i = 0;
    while(tab && tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

// #include <stdio.h>

void free_incomplete_array(void **array, int max)
{
    if (!array || !(*array) || max < 0)
        return ;
    for (int i = 0; i < max; ++i) {
        if (array[i])
           free(array[i]);
    }
    free(array);
}