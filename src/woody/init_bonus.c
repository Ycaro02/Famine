#include <woody.h>
#include <parse_flag/parse_flag.h>

#define HELP_MSG "Usage: %s [OPTION]... [ELF_FILE]\n\
-v, --verbose: verbose set log level to INFO\n\
-h, --help: help display this message\n\
-s, --size: \"VALUE\" key size set the key size to encrypt the binary ( min 16 bytes, max 256 bytes, MUST be multiple of 2 )\n\
-k, --key: \"VALUE\" key set the key to encrypt the binary ( in hexadecimal so 32 bytes long for the default len 16 )\n\
-c, --command: \"VALUE\" command to execute after decryption ( 1 for execute command, 2 for display custom message )\n\
-a, --argument: \"VALUE\" argument to pass to the command or custom message ( max 240 bytes )\n"


/**
 * @brief Get option value from flag context
 * @param opt_lst option list
 * @param flag flag value
 * @param to_find flag to find
 * @return allocated copy option value or NULL if not found
 */
static void *get_value_from_opt(t_list *opt_lst, uint32_t flag, uint32_t to_find) {
	OptNode	*opt = NULL;
	void		*ret = NULL;

	if (has_flag(flag, to_find)) {
		opt = search_exist_opt(opt_lst, is_same_flag_val_opt, (void *)&to_find);
		if (opt && opt->value_type == DECIMAL_VALUE) {
			ret = malloc(sizeof(u32));
            t_list *val_node = opt->val_lst;
            if (val_node) {
                U_OptValue *val = (U_OptValue *)val_node->content;
                *(u32 *)ret = val->digit;
            }
			// *(u32 *)ret = opt->val.digit;
		} else if (opt && (opt->value_type == HEXA_VALUE || opt->value_type == CHAR_VALUE)) {
			t_list *val_node = opt->val_lst;
            if (!val_node)
                return (NULL);
            U_OptValue *val = (U_OptValue *)val_node->content;
            ret = ft_strdup(val->str);
            // ret = ft_strdup(opt->val.str);
		}
	}
	return (ret);
}

static s8 command_option_handling(UserInput *input, FlagContext *flag_c) {
	u32 *uint_ptr = NULL;
	
	if (has_flag(input->flag, FLAG_COMMAND)) {
		if (!has_flag(input->flag, FLAG_ARG)) {
			LOG(L_ERROR, "Command given but no argument set\n");
			goto error_case;
		}
		uint_ptr = get_value_from_opt(flag_c->opt_lst, FLAG_COMMAND, FLAG_COMMAND);
		input->command = *uint_ptr;
		free(uint_ptr);
		LOG(L_INFO, ORANGE"COMMAND: %u\n"RESET, input->command);
		if (input->command != CMD_EXEC && input->command != CMD_CUSTOM_MSG) {
			LOG(L_ERROR, "Command given: %u -> must be 1 for execute command or 2 for display custom message\n", input->command);
			goto error_case;
		}
	}

	if (has_flag(input->flag, FLAG_ARG)) {
		if (!has_flag(input->flag, FLAG_COMMAND)) {
			LOG(L_ERROR, "Argument given but no command set\n");
			goto error_case;
		}
		input->arg = get_value_from_opt(flag_c->opt_lst, FLAG_ARG, FLAG_ARG);
		LOG(L_INFO, ORANGE"ARGUMENT: %s\n"RESET, input->arg);
		if (ft_strlen(input->arg) > ARG1_ACCEPTED_SIZE) {
			LOG(L_ERROR, "Argument given len: %zu -> must be less than %u bytes\n", ft_strlen(input->arg), ARG1_ACCEPTED_SIZE);
			goto error_case;
		}
		input->arg_len = ft_strlen(input->arg);
	}

	return (TRUE);

	error_case:
		input_destroy(input);
		free_flag_context(flag_c);
		return (FALSE);
}

static s8 key_option_handling(UserInput *input, FlagContext *flag_c) {

	u32 *uint_ptr = NULL;

	if  (has_flag(input->flag, FLAG_KEY_SIZE)) {
		uint_ptr = get_value_from_opt(flag_c->opt_lst, FLAG_KEY_SIZE, FLAG_KEY_SIZE);
		input->key_len = *uint_ptr;
		free(uint_ptr);
		LOG(L_INFO, ORANGE"KEY SIZE: %u\n"RESET, input->key_len);
		if (input->key_len < KEY_LEN_MIN || input->key_len > KEY_LEN_MAX || input->key_len % 2 != 0) {
			LOG(L_ERROR, "Key size given: %u -> must be between %u and %u and must be multiple of 2\n", input->key_len, KEY_LEN_MIN, KEY_LEN_MAX);
			goto error_case;
		}
	}

	if (has_flag(input->flag, FLAG_KEY)) {
		input->key = get_value_from_opt(flag_c->opt_lst, FLAG_KEY, FLAG_KEY);
		LOG(L_INFO, ORANGE"KEY: %s\n"RESET, input->key);
		if (ft_strlen(input->key) != input->key_len * 2U) {
			LOG(L_ERROR, "Key given len: %zu -> must be %u bytes long for keylen : %u (keylen * 2) \n", ft_strlen(input->key), input->key_len * 2U, input->key_len);
			goto error_case;
		}
	}

	return (TRUE);

	error_case:
		if (input->key) {
			free(input->key);
		}
		free(input->path);
		free_flag_context(flag_c);
		return (FALSE);
}

static s8 file_name_get(int argc , char **argv, UserInput *input, FlagContext *flag_c) {
	t_list 			*args = NULL;
	s32				nb_args = 0;

	args = extract_args(argc, argv);
	nb_args = ft_lstsize(args);
	if (nb_args != 1) {
		ft_printf_fd(1, HELP_MSG, argv[0]);
		free_flag_context(flag_c);
		return (FALSE);
	}
	input->path = ft_strdup((char *)args->content);
	ft_lstclear(&args, free);
	
	return (TRUE);
}

typedef struct flag_struct_opt {
    char                *full_name;                 /* Full option name */
    char                flag_char;                  /* Short option character */
    u32                 flag_val;                   /* Flag value */
    E_OptValueType      value_type;                 /* Type of value */
    E_OptValueOverride  override_type;              /* Override type */
    u32                 min_val;                    /* Minimum value */
    u32                 max_val;                    /* Maximum value */
    void                *custom_function_pointer;   /* Custom function pointer */
    s8                  add_value_after_parse;      /* Add value after parse */
} FlagStructOpt;

FlagContext *init_famine_flag_context(int argc, char **argv, u32 *out_flag, FlagStructOpt *server_opt_array) {
    FlagContext *c = flag_context_init(argv);
    if (!c) {
        ERR("Failed to initialize flag context.\n");
        return (NULL);
    }

    for (int i = 0; server_opt_array[i].full_name != NULL; i++) {
        FlagStructOpt opt = server_opt_array[i];
        s8 res = add_flag_option(c, opt.full_name, opt.flag_val, opt.flag_char);
        if (!res) {
            ERR("Failed to add flag option: %s\n", opt.full_name);
            // Clean up if necessary
            return (NULL);
        }
        set_flag_option(c, opt.flag_val, EOPT_VALUE_TYPE, opt.value_type);
        set_flag_option(c, opt.flag_val, EOPT_MULTIPLE_VAL, opt.override_type);
        set_flag_option(c, opt.flag_val, EOPT_MIN_VAL, opt.min_val);
        set_flag_option(c, opt.flag_val, EOPT_MAX_VAL, opt.max_val);
        set_flag_option(c, opt.flag_val, EOPT_PARSE_FUNC, opt.custom_function_pointer);
        set_flag_option(c, opt.flag_val, EOPT_ADD_VAL_AFTER_PARSE, opt.add_value_after_parse);
    }

    *out_flag = parse_flag(argc, argv, c, &c->error);

    if (c->error) {
        ERR("Error parsing flags.\n");
        free_flag_context(c);
        return (NULL);
    }

    if (*get_log_level() == L_DEBUG) {
        display_flags(c->opt_str, *out_flag);
        display_option_list(*c);
    }
    

    return (c);
}


s8 woody_bonus_init(char **argv, UserInput *input, int argc) {

    FlagStructOpt server_opt_array[] = {
        {"verbose", 'v', FLAG_VERBOSE, OPT_NO_VALUE, VALUE_NO_OVERRID, 0, 0, NULL, FALSE},
        {"help", 'h', FLAG_HELP, OPT_NO_VALUE, VALUE_NO_OVERRID, 0, 0, NULL, FALSE},
        {"key", 'k', FLAG_KEY, HEXA_VALUE, VALUE_NO_OVERRID, 0, KEY_LEN_MAX * 2U, NULL, TRUE},
        {"size", 's', FLAG_KEY_SIZE, DECIMAL_VALUE, VALUE_NO_OVERRID, KEY_LEN_MIN, KEY_LEN_MAX, NULL, TRUE},
        {"command", 'c', FLAG_COMMAND, DECIMAL_VALUE, VALUE_NO_OVERRID, 1U, 2U, NULL, TRUE},
        {"argument", 'a', FLAG_ARG, CHAR_VALUE, VALUE_NO_OVERRID, 0, ARG1_ACCEPTED_SIZE, NULL, TRUE},
        {NULL, 0, 0, 0, 0, 0, 0, NULL, 0}
    };


    FlagContext *flag_c = init_famine_flag_context(argc, argv, &input->flag, server_opt_array);
    if (!flag_c) {
        return (FALSE);
    }

	flag_c->prg_name = argv[0];

	if (!file_name_get(argc, argv, input, flag_c)) {
		return (FALSE);
	} else if (has_flag(input->flag, FLAG_HELP)) {
		ft_printf_fd(1, HELP_MSG, argv[0]);
		free(input->path);
		free_flag_context(flag_c);
		return (FALSE);
	}  
	
	if (has_flag(input->flag, FLAG_VERBOSE)) {
		set_log_level(L_INFO);
	} 
	
	if (!key_option_handling(input, flag_c)) {
		return (FALSE);
	} else if (!command_option_handling(input, flag_c)) {
		return (FALSE);
	}
	
	free_flag_context(flag_c);
	return (TRUE);
}

