#ifndef BITSHIFT_UTILS_HEADER_H
# define BITSHIFT_UTILS_HEADER_H

#include "basic_define.h"

/* Mask */
#define BYTE1_MASK 0xFF000000
#define BYTE2_MASK 0x00FF0000
#define BYTE3_MASK 0x0000FF00
#define BYTE4_MASK 0x000000FF

/* Shift */
#define BYTE1_SHIFT 24
#define BYTE2_SHIFT 16
#define BYTE3_SHIFT 8
#define BYTE4_SHIFT 0

FT_INLINE s32 s32StoreValues(u8 val1, u8 val2, u8 val3, u8 val4) {
	return ((val1 << BYTE1_SHIFT) | (val2 << BYTE2_SHIFT) | (val3 << BYTE3_SHIFT) | val4);
}

FT_INLINE u8 s32ValueGet(s32 container, u8 shift) {
	return ((container & (0xFF << shift)) >> shift);
}

FT_INLINE u8 s32ValueGetByte(s32 container, u8 byte) {
	return (container & (0xFF << (byte * 8))) >> (byte * 8);
}

/* Store bits value (0 or 1) in byte */
FT_INLINE u8 u8StoreValues(u8 val1, u8 val2, u8 val3, u8 val4, u8 val5, u8 val6, u8 val7, u8 val8) {
	return ((val1 << 7) | (val2 << 6) | (val3 << 5) | (val4 << 4) | (val5 << 3) | (val6 << 2) | (val7 << 1) | val8);
}

FT_INLINE u8 u8ValueGet(u8 container, u8 byte) {
	return ((container & (1 << byte)) >> byte);
}

FT_INLINE u8 u8ValueSet(u8 container, u8 byte, u8 value) {
	return ((container & ~(1 << byte)) | (value << byte));
}

#endif /* !BITSHIFT_UTILS_HEADER_H */