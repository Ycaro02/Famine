#include "../basic_define.h"

FT_INLINE s8 is_prime(u64 nb) {
	u64	i = 3;
	
    if (nb == 2) {
		return (1);
    }
	if (nb <= 1 || nb % 2 == 0) {
		return (0);
    }
	while (i < nb / 2) {
		if (nb % i == 0) {
			return (0);
        }
		i += 2;
	}
	return (1);
}

FT_INLINE u64 find_next_prime(u64 nb) {
	if (nb <= 1)
		return (2U);
	while (is_prime(nb) == 0) {
		nb++;
    }
	return (nb);
}

#define GET_NEXT_PRIME(nb) (is_prime(nb) ? nb : find_next_prime(nb))