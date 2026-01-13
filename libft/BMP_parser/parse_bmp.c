#include "parse_bmp.h"

/**
 * @brief Display the content of the BMP header and info header
 * @param header pointer to the BMP header
 * @param info pointer to the BMP info header
*/
// FT_INLINE void display_bmp_hdr_data(bmp_hdr *header, bmp_info_hdr *info) {
//     /* display size of structure */    
//     ft_printf_fd(1, "Size of BMP Header: %d\n", BMP_HDR_SIZE);
//     ft_printf_fd(1, "Size of BMP Info Header: %d\n", BMP_INFO_HDR_SIZE);
  
//     /* display header struct field  */
//     ft_printf_fd(1, "Type: %c%c\n", (char)header->type, (char)(header->type >> 8));
//     ft_printf_fd(1, "Size: %d\n", header->size);
//     ft_printf_fd(1, "Reserved1: %d\n", header->reserved1);
//     ft_printf_fd(1, "Reserved2: %d\n", header->reserved2);
//     ft_printf_fd(1, "Offset: %d\n", header->offset);
  
//     /* display header info field */
//     ft_printf_fd(1, "Size: %d\n", info->size);
//     ft_printf_fd(1, "Width: %d\n", info->width);
//     ft_printf_fd(1, "Height: %d\n", info->height);
//     ft_printf_fd(1, "Planes: %d\n", info->planes);
//     ft_printf_fd(1, "Bits: %d\n", info->bits);
//     ft_printf_fd(1, "Compression: %d\n", info->compression);
//     ft_printf_fd(1, "ImageSize: %d\n", info->imagesize);
//     ft_printf_fd(1, "XResolution: %d\n", info->xresolution);
//     ft_printf_fd(1, "YResolution: %d\n", info->yresolution);
//     ft_printf_fd(1, "NColours: %d\n", info->ncolours);
//     ft_printf_fd(1, "ImportantColours: %d\n", info->important_colours);
// }

/**
 * @brief Load a file into memory using mmap
 * @param path path to the file to read
 * @param file_size pointer to store the file size
 * @return pointer to the file in memory 
*/
FT_INLINE u8 *load_mmap_file(char *path, u64 *file_size, u32 min_size)
{
    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        ft_printf_fd(2, "Failed to open file %s\n", path);
        return (NULL);
    }

    struct stat st;

    ft_bzero(&st, sizeof(st));
    fstat(fd, &st);
    *file_size = st.st_size;

    if (*file_size <= min_size) {
        close(fd);
        ft_printf_fd(2, "File %s is no enought large to contain BMP header %u\n", path, *file_size);
        return (NULL);
    }

    void *map = mmap(0, *file_size, PROT_READ, MAP_PRIVATE, fd, 0);

    if (map == MAP_FAILED) {
        close(fd);
        ft_printf_fd(2, "Failed to open file %s\n", path);
        return (NULL);
    }
    return (map);
}


FT_INLINE u8 check_file_size(u8 *file, u64 file_size, bmp_hdr header, bmp_info_hdr info, int data_size) {
    u8 *end_ptr = file + file_size;
    u8 *estimate_end = file + header.offset + (info.width * info.height * data_size);
    
	if (end_ptr != estimate_end) {
        ft_printf_fd(2, "Invalid file size, estimated end ptr %p, real end %p\n", (void *)estimate_end, (void *)end_ptr);
        return (0);
    } 
	return (1);
}

u8 *imageFlip180(u8 *image, int width, int height, int type)
{
    int data_size = type == 3 ? RGB_SIZE : RGBA_SIZE;
    u8 *flipped_image = ft_calloc(width * height * data_size, sizeof(u8));

    if (!flipped_image) {
        return (NULL);
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            u8 *pixel = image + (i * width + j) * data_size;
            u8 *flipped_pixel = flipped_image + ((height - i - 1) * width + (width - j - 1)) * data_size;
            ft_memcpy(flipped_pixel, pixel, data_size);
        }
    }
	return (flipped_image);
}

u8 *imageFlip90(u8 *image, int width, int height, int type)
{
    int data_size = type == 3 ? RGB_SIZE : RGBA_SIZE;
    u8 *flipped_image = malloc(width * height * data_size);

    if (!flipped_image) {
        return (NULL);
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            u8 *pixel = image + (i * width + j) * data_size;
            u8 *flipped_pixel = flipped_image + (j * height + i) * data_size;
            ft_memcpy(flipped_pixel, pixel, data_size);
        }
    }
    return (flipped_image);
}

/**
 * @brief Parse a BMP file and return the image data
 * @param path path to the BMP file
 * @param width pointer to store the width of the image
 * @param height pointer to store the height of the image
 * @param type pointer to store the type of the image
 * @return pointer to the image data
*/
u8 *parse_bmp_file(char* path, int *width, int *height, int *type)
{
	bmp_hdr         header;
    bmp_info_hdr    info;
    u64				file_size = 0;
    u8				*file = load_mmap_file(path, &file_size, BMP_HDR_TOTAL_SIZE);
    int				data_size = RGB_SIZE;

    if (file == NULL) {
        ft_printf_fd(2, "mmap failled to load file %s\n", path);
        return (NULL);
    }
	/* fill bmp header structure */
    ft_memcpy(&header, file, BMP_HDR_SIZE);
    ft_memcpy(&info, file + BMP_HDR_SIZE, BMP_INFO_HDR_SIZE);

	/* Display the content of the BMP header and info header */
	// display_bmp_hdr_data(&header, &info);

	/* Detect data type rgb or rgba and fill type ptr */
    if (info.bits == RGB_BITS) {
        *type = 3;
    } else if (info.bits == RGBA_BITS) {
        *type = 4;
        data_size = RGBA_SIZE;
    } else {
		munmap(file, file_size);
		ft_printf_fd(2, "Invalid bmp file %s bits per pixel %d\n", path, info.bits);
		return (NULL);
	}

	/* fill width height ptr */
    *width = info.width;
    *height = info.height;

	
	/* Basic protection check the amount of data */
	if (!check_file_size(file, file_size, header, info, data_size)) {
		munmap(file, file_size);
		return (NULL);
	}

	/* Alloc the data unsigned char array */
    u8 *image = malloc(info.width * info.height * data_size);
    if (!image) {
		munmap(file, file_size);
        return (NULL);
    }

	/* Start read at header.offset */
    u8 *read_ptr = file + header.offset;
    for (int i = 0; i < info.height; i++) {
        for (int j = 0; j < info.width; j++) {
			/* We need to reverse B and R value, bmp store data with BGR format not RGB (endianess) */
            u8 *pixel = image + (i * info.width + j) * data_size;
            pixel[0] = read_ptr[2];		/* R */ 
            pixel[1] = read_ptr[1];		/* G */ 
            pixel[2] = read_ptr[0];		/* B */ 
            if (data_size == 4) {
                pixel[3] = read_ptr[3];	/* A */ 
            }
            read_ptr += data_size;
        }
    }
	munmap(file, file_size);
    return (image);
}