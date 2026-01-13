#include "../libft.h"

int ftlib_strcpy(char* dst, char *src, int len)
{
    int i = 0;
    if (!src || len < 1)
        return (0);
    while (src[i]) {
        dst[i] = src[i];
        i++;
    }
    return (len);
}   