#include <woody.h>

int process_woody(int argc, char **argv) {
	UserInput	input = {0};
	int 		ret = 0;

	// set_log_level(L_INFO);

	input.key_len = KEY_LEN;

	#ifdef WOODY_BONUS
		ret = woody_bonus_init(argv, &input, argc);
		if (!ret) { return (1); }
	#else
		if (argc != 2) {
			ft_printf_fd(1, "Usage: %s <elf_file>\n", argv[0]);
			return (1);
		}
		input.path = ft_strdup(argv[1]);
	#endif

	ret = woody_woodpacker(&input);
	return (ret);
}
