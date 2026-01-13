#ifndef PARSE_BPM_HEADER
#define PARSE_BPM_HEADER 1

#include "../libft.h"

#include <sys/mman.h>   /* mmap header */
#include <sys/stat.h>   /* fstat */

/* Mandatory to pack this, 14 bytes always rounded too 16 by compiler */
typedef struct PACKED_STRUCT s_bmp_hdr {
    u16 type;           			/* file type. this should be 'BM'. */
    u32 size;           			/* Total file size in bytes */
    u16 reserved1;      			/* reserved field typically set to 0 */
    u16 reserved2;					/* reserved field typically set to 0 */
    u32 offset;         			/* offset in byte, where the data start */
} bmp_hdr;

/* BMP info header */
typedef struct s_bmp_info_hdr {
    u32 size;                       /* Size of this info header */
    int width, height;              /* width and height of img in pixel */
    u16 planes;                     /* number of planes */
    u16 bits;                       /* number of bits per pixel */
    u32 compression;                /* type of compression */
    u32 imagesize;                  /* size of image data in bytes, ig no compressed data can be set to 0 */
    int xresolution, yresolution;   /* resolution in pixels per meter */
    u32 ncolours;                   /* number of colours used by the bitmap */
    u32 important_colours;          /* number of important colours, 0 means all are important */
} bmp_info_hdr;

#define BMP_HDR_SIZE (sizeof(bmp_hdr))
#define BMP_INFO_HDR_SIZE (sizeof(bmp_info_hdr))
#define BMP_HDR_TOTAL_SIZE (BMP_HDR_SIZE + BMP_INFO_HDR_SIZE)

#define RGB_SIZE (sizeof(u8) * 3)
#define RGB_BITS (u32)(8 * 3)
#define RGBA_SIZE (sizeof(u8) * 4)
#define RGBA_BITS (u32)(8 * 4)

/**
 * @brief Parse a BMP file and return the image data
 * @param path path to the BMP file
 * @param width pointer to store the width of the image
 * @param height pointer to store the height of the image
 * @param type pointer to store the type of the image
 * @return pointer to the image data
*/
u8 *parse_bmp_file(char* path, int *width, int *height, int *type);

/**
 * @brief Cut a texture into squares of a given width and height
 * @param texture The texture to cut
 * @param tex_width The width of the texture
 * @param tex_height The height of the texture
 * @param width The width of the squares
 * @param height The height of the squares
 * @param type The number of bytes per pixel (3 for RGB, 4 for RGBA)
 * @return t_list pointer to the list of squares, each content node is a texture square
*/
t_list *cut_texture_into_squares(u8* texture, int tex_width, int tex_height, int width, int height, int type);

/**
 * @brief Flip an image vertically
 * @param image pointer to the image to flip
 * @param width width of the image
 * @param height height of the image
 * @param type number of bytes per pixel (3 for RGB, 4 for RGBA)
 * @return pointer to the flipped image
*/
u8 *imageFlip180(u8 *image, int width, int height, int type);


u8 *imageFlip90(u8 *image, int width, int height, int type);

#endif /* PARSE_BPM_HEADER */