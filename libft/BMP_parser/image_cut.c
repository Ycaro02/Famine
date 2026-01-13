#include "parse_bmp.h"

#define PINK_VEC (vec3_u8){255, 0, 255}

s8 is_square_empty(u8* square, int width, int height, int type) {
	vec3_u8 firstColor = {0,0,0};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int square_index = (y * width + x) * type;

			if (y == 0 && x == 0) {
				firstColor[0] = square[square_index];
				firstColor[1] = square[square_index + 1];
				firstColor[2] = square[square_index + 2];
			}

			if (!(square[square_index] == firstColor[0] && square[square_index + 1] == firstColor[1] && square[square_index + 2] == firstColor[2])) {
				return (FALSE);
			}
        }
    }
    return (TRUE);
}

t_list *cut_texture_into_squares(u8* texture, int tex_width, int tex_height, int width, int height, int type) {
    int num_squares_x = tex_width / width;
    int num_squares_y = tex_height / height;
    int square_count = 0;
    t_list *square_lst = NULL;

    for (int i = 0; i < num_squares_y; i++) {
        for (int j = 0; j < num_squares_x; j++) {
            u8* square = malloc(width * height * type);  /* type bytes per pixel (RGB or RGBA) */
            if (!square) {
                ft_printf_fd(2, "Failed to allocate memory for image square\n");
                return (NULL);
            }

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    int tex_index = ((i * height + y) * tex_width + (j * width + x)) * type;
                    int square_index = (y * width + x) * type;
                    ft_memcpy(&square[square_index], &texture[tex_index], type);
                }
            }
			if (is_square_empty(square, width, height, type)) {
					free(square);
					square = NULL;
			} else {
				if (height == 16) {
					u8 *reverse = imageFlip180(square, width, height, type);
                	ft_lstadd_back(&square_lst, ft_lstnew(reverse));
					free(square);
				} else {
					ft_lstadd_back(&square_lst, ft_lstnew(square));
				}
                square_count++;
            }
        }
    }
    ft_printf_fd(1, CYAN"Cut texture %d*%d into %d squares of %d\n"RESET, tex_width, tex_height, square_count, width);
    return (square_lst);

}