#include <stdint.h>
#include <stddef.h>
#include "../basic_define.h"

#define BYTE_DECREMENT_MASK	0x0101010101010101ULL
#define MSB_MASK			0x8080808080808080ULL

int ft_strcmp(const char *s1, const char *s2)
{
	const u64 *p1, *p2;
	
    /* Align to 8-byte boundary */
    while (((uintptr_t)s1 & 7) && *s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }

	/* Compare 8 bytes at a time */
	p1 = (const u64 *)s1;
	p2 = (const u64 *)s2;
    while (*p1 == *p2)
    {
		/* If one of the bytes in the 8-byte block is a null byte, we've reached the end of the string */
        if (((*p1 - BYTE_DECREMENT_MASK) & ~*p1 & MSB_MASK) != 0)
            break;
        p1++;
        p2++;
    }

	/* Compare the remaining bytes */
    s1 = (const char *)p1;
    s2 = (const char *)p2;
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }

    return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}


int fast_strlen(const char *s)
{
	const char *p = s;
	const u64 *lp;
	u64 word;

	/* Align to 8-byte boundary */
	while (((uintptr_t)p & 7) && *p)
		p++;

	/* Count 8 bytes at a time */
	lp = (const u64 *)p;
	while (1)
	{
		word = *lp;
		if (((word - BYTE_DECREMENT_MASK) & ~word & MSB_MASK) != 0)
			break;
		lp++;
	}

	/* Count the remaining bytes */
	p = (const char *)lp;
	while (*p)
		p++;

	return (p - s);
}

char *fast_strcpy(char *dst, const char *src)
{
	char *ret = dst;
	const u64 *p1;
	u64 *p2;
	u64 word;

	/* Align to 8-byte boundary and copy bytes */
	while (((uintptr_t)src & 7) && *src)
		*dst++ = *src++;

	/* Copy 8 bytes at a time */
	p1 = (const u64 *)src;
	p2 = (u64 *)dst;
	while (1)
	{
		word = *p1;
		*p2 = word;
		if (((word - BYTE_DECREMENT_MASK) & ~word & MSB_MASK) != 0)
			break;
		p1++;
		p2++;
	}

	/* Copy the remaining bytes */
	src = (const char *)p1;
	dst = (char *)p2;
	while (*src)
		*dst++ = *src++;

	*dst = '\0';
	return (ret);
}

void fast_bzero(void *s, size_t n)
{
	u64 *p = (u64 *)s;
	u64 word = 0;
	u8 *p2;

	/* Set 8 bytes at a time */
	while (n >= 8)
	{
		*p++ = word;
		n -= 8;
	}

	/* Set the remaining bytes */
	p2 = (u8 *)p;
	while (n--)
		*p2++ = 0;
}