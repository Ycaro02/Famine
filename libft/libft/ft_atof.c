#include "../libft.h"

u8 str_is_float(char *str)
{
	u8 point_found = 0;

	if (!str) {
		return (FALSE);
	} else if (*str == '-') {
		str++;
	}
	while (*str) {
		if (*str == '.') {
			if (point_found) {
				return (FALSE);
			}
			point_found = 1;
		} else if (!ft_isdigit(*str)) {
			return (FALSE);
		}
		str++;
	}
	return (TRUE);

}

float ft_atof(char *str)
{
	/* Create result and neg var */
	double res = 0, neg = 1;
	/* decimal var for decimal parts compute */
	double dec = 0.1;

	if (!str) {
		return (0);
	} else if (*str == '-') { /* if first is '-' neg = -1 and skip it */
		neg = -1;
		str++;
	}

	/* like atoi just add digit ony by one with * 10 */
	while (*str >= '0' && *str <= '9') {
		res = res * 10 + *str - '0';
		str++;
	}
	/* check for decimal parts */
	if (*str && *str == '.') { 
		str++; /* skip dot */
		/* same logic than atoi, but /10 each iterate instead of *10 */
		while (*str && *str >= '0' && *str <= '9') {
			res += (*str - '0') * dec;
			dec *= 0.1;
			str++;
		}
	}
	return ((res * neg));
}
