#include "../libft.h"

static char	*ft_make(long int n, char *dst, int count, int sign)
{
	if (n == 0)
	{
		dst = ft_calloc(sizeof(char), 2);
		dst[0] = '0';
		dst[1] = '\0';
		return (dst);
	}
	dst = ft_calloc(sizeof(char), count + 1);
	if (dst == NULL)
		return (NULL);
	count--;
	while (count >= sign)
	{
		dst[count] = (n % 10) + 48;
		n /= 10;
		count--;
	}
	if (sign == 1)
		dst[0] = '-';
	return (dst);
}

char	*ft_ltoa(long n)
{
	int			count;
	char		*dst;
	long long	tmp;
	int			sign;	
	long long 	nbr;

	dst = NULL;
	nbr = (long long)n;
	sign = 0;
	count = 0;
	if (nbr < 0)
	{
		nbr = (long long)n * -1;
		sign = 1;
		count++;
	}
	tmp = nbr;
	while (tmp != 0)
	{
		tmp /= 10;
		count++;
	}
	dst = ft_make(nbr, dst, count, sign);
	return (dst);
}


static char	*ft_make_ul(unsigned long n, char *dst, int count)
{
	if (n == 0)
	{
		dst = ft_calloc(sizeof(char), 2);
		dst[0] = '0';
		dst[1] = '\0';
		return (dst);
	}
	dst = ft_calloc(sizeof(char), count + 1);
	if (dst == NULL)
		return (NULL);
	count--;
	while (count >= 0)
	{
		dst[count] = (n % 10) + 48;
		n /= 10;
		count--;
	}
	return (dst);
}

char	*ft_ultoa(unsigned long n)
{
	int				count;
	char			*dst;
	unsigned long	tmp;

	dst = NULL;
	count = 0;
	tmp = n;
	while (tmp != 0) {
		tmp /= 10;
		count++;
	}
	dst = ft_make_ul(n, dst, count);
	return (dst);
}