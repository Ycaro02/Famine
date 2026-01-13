#include "parse_flag.h"

/**
* 00000000 -> Our current flag value is 0
* | 00000100 -> Do or operation with Flag3, which has a value of 4
* = 00000100 -> The bit for Flag3 gets set to 1, flag value is now 4
* Enable target flag
*/
void set_flag(u32 *flags, u32 flag_val)
{
    if (flags)
        *flags |= flag_val;
}

/**
* 00000100 -> We get Flag3 as input to unset
* ~= 11111011 -> We flip all the bits of Flag3
* 00010110 -> Our current value had Flag2, 3 and 5 set already
* &  11111011 -> AND operation with the result of previous inversion
* =  00010010 -> Our new value only has Flag2 and 5 set
* Disable target flag
*/
void unset_flag(u32 *flags, u32 flag_val)
{
    if (flags)
        *flags &= ~flag_val;
}


/**
 * 00010110 -> Starting value has Flag2, Flag3 and Flag5 set
 * ^ 00000100 -> Perform XOR with Flag3
 * = 00010010 -> Result is equal to Flag2 and Flag5
 * Reverse target flag
*/
void reverse_flag(u32 *flags, u32 flag_val)
{
	if (flags)
		*flags ^= flag_val;
}

/*
* 00010110 -> Starting value has Flag2, Flag3 and Flag5 set
* & 00000100 -> Perform & with Flag3
* = 00000100 -> Result is equal to Flag3
* check if flag_val enable in flags
// __always_inline int has_flag(int flags, int flag_val)
*/

s8 has_flag(u32 flags, u32 flag_val) {
   return ((flags & flag_val) == flag_val);
}

s8 flag_already_present(u32 flags, u32 flag_val) {
    return (has_flag(flags, flag_val));
}