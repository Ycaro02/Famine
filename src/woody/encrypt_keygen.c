#include <elf_getter.h>
#include <woody.h>

#define U8_ERROR 256

static u16 random_u8_get(int fd) {
	u8 val = 0, ret = 0;
	ret = read(fd, &val, 1);
	if (ret != 1) {
		LOG(L_ERROR, "Can't read from /dev/urandom\n");
		return (U8_ERROR);
	}
	return (val % 255);
}

static void display_key(char *msg, u8 *key, u32 key_len) {
	char display_key[1024];

	ft_bzero(display_key, 1024);
	for (u32 i = 0; i < key_len; i++) {
		sprintf(display_key + (i * 2), "%02x", key[i]);
	}
	INFO(YELLOW"Key %s: |%s|\n"RESET, msg, display_key);
}

/**
 * @brief Generate a random key
 * @param key The key to generate
 * @param key_len The length of the key
 */
u8 *keygen(u32 key_len) {
	u8 *key = NULL;
	int fd = -1;
	u16 key_char = 0;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0) {
		LOG(L_ERROR, "Can't open /dev/urandom\n");
		return (NULL);
	} else if (!(key = ft_calloc(key_len, 1))) {
		LOG(L_ERROR, "Can't allocate memory for the key\n");
		close(fd);
		return (NULL);
	}
	
	for (u32 i = 0; i < key_len; i++) {
		key_char = random_u8_get(fd);
		if (key_char == U8_ERROR) {
			free(key);
			close(fd);
			return (NULL);
		}
		key[i] = key_char;
	}
	display_key("generated", key, key_len);
	return (key);
}

/**
 * @brief Convert a char to hexa
 * @param c char to convert
 * @return hexa value
 */
static uint8_t char_to_hexa(char c)
{
	if (ft_isdigit(c)) {
		return (c - '0');
	} else if (ft_isalpha(c)) {
		if (c >= 'A' && c <= 'F') {
			return (c - 'A' + 10);
		} else {
			return (c - 'a' + 10);
		}
	}
	return (0);
}

/**
 * @brief Fill a buffer with hexa value from a char data
 * @param buff buffer to fill
 * @param data data to convert
 * @param size size of the buffer (key_len)
 */
u8 *fill_hexa_buff(char *data, u32 size)
{
	u8	*buff = NULL;
	u32	i = 0, j = 0;

	if (!(buff = (u8 *)ft_calloc(size, 1))) {
		return (NULL);
	}

	while (j < size) {
		buff[j] = (char_to_hexa(data[i]) << 4);
		++i;
		buff[j] |= char_to_hexa(data[i]);
		++i; ++j;
	}

	display_key("copy", buff, size);

	return (buff);
}

