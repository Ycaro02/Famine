#include "parse_flag.h"

/* Start option handle */
/**
 * @brief Display option list for debug
*/
void display_option_list(FlagContext flag_c)
{
    OptNode	*node = NULL;
	s32		i = 0; 
	ft_printf_fd(2, CYAN"Option list: Full flag str: |%s|\n"RESET, flag_c.opt_str);
    for (t_list *tmp = flag_c.opt_lst; tmp; tmp = tmp->next) {
        node = tmp->content;
		ft_printf_fd(1, "--------------------------------------------------------------------------------------------------------------------------------");
        ft_printf_fd(1, CYAN"\nFlag: [-%c] "PURPLE"Power [%d] "YELLOW" Name |%s|"RESET","GREEN" Min :[%d] "RED"Max [%d] "ORANGE" mult_val: [%s] "BLUE"nb: [%d] "PURPLE"Func: [%s] "YELLOW"Store: [%d]\n"RESET
        , node->flag_char, node->flag_val, node->full_name, node->min_val, node->max_val, node->multiple_val == VALUE_APPEND ? "append" : node->multiple_val == VALUE_OVERRID ? "override" : "No override", node->nb_stored_val, node->parse ? "Yes" : "No", node->add_value_after_parse);
    
		for (t_list *val_lst = node->val_lst; val_lst; val_lst = val_lst->next) {
			U_OptValue *val = val_lst->content;
			
			ft_printf_fd(1, CYAN"[%d]: "RESET, i);
			if (node->value_type == DECIMAL_VALUE) {
				ft_printf_fd(1, ORANGE"|%u|\n"RESET, val->digit);
			}
			else if (node->value_type != OPT_NO_VALUE) {
				ft_printf_fd(1, ORANGE"|%s|"RESET" -> "YELLOW"len [%d]\n"RESET, val->str, ft_strlen(val->str));
			} 
			else {
				ft_printf_fd(1, "No value\n");
			}
			i++;
		}
		ft_printf_fd(1, "--------------------------------------------------------------------------------------------------------------------------------\n");
		i = 0;

	}
}

/**
 * @brief Check if node full name is the same as data
 * @param node node to check
 * @param data data to compare
*/
s8 is_same_full_name(void *node, void *data) {
    if (!node || !data)
        return (0);
    return (ft_strncmp(((OptNode *)node)->full_name, (char *)data, ft_strlen(((OptNode *)node)->full_name)) == 0);
}

/**
 * @brief Check if content flag char is the same as c
 * @param content content to check
 * @param c char to compare
*/
s8 is_same_char_opt(void *content, void *c) {
    if (!content || !c)
        return (0);
    return (((OptNode *)content)->flag_char == *(u8 *)c);
}

/**
 * @brief Check if content flag val is the same as value
 * @param content content to check
 * @param value value to compare
*/
s8 is_same_flag_val_opt(void *content, void *value) {
    if (!content || !value)
        return (0);
    return (((OptNode *)content)->flag_val == *(u32 *)value);
}

/**
 * @brief Search for exist opt
 * @param opt_lst list of opt node
 * @param cmp compare function
 * @param data data to compare
 * @return opt_node if found, NULL otherwise
*/
void *search_exist_opt(t_list *opt_lst, s8 (cmp(void *, void *)), void *data)
{
    for (t_list *tmp = opt_lst; tmp; tmp = tmp->next) {
        if (cmp(tmp->content, data)) {
            return (tmp->content);
        }
    }
    return (NULL);
}

/**
 *	@brief Create option node
 *	@param c flag char
 *	@param flag_val flag value
 *	@param value value
 *	@param full_name full name of the flag
 *	@return opt_node if success, NULL otherwise
*/
static OptNode *create_opt_node(u8 c, u32 flag_val, char *full_name)
{
    OptNode *opt = ft_calloc(sizeof(OptNode), 1);

    if (!opt) {
        ft_printf_fd(2, "Failed to allocate memory for opt\n");
        return (NULL);
    }
    opt->flag_char = c;
    opt->flag_val = flag_val;
	opt->val_lst = NULL;
    opt->full_name = ft_strdup(full_name);
	opt->parse = NULL;

    opt->has_value = FALSE;
	opt->multiple_val = VALUE_NO_OVERRID;
	opt->value_type = OPT_NO_VALUE;
	opt->max_val = DEFAULT_MAX_VAL;
	opt->min_val = OPT_NO_VALUE;
	opt->add_value_after_parse = TRUE;
	// ft_printf_fd(2, RED"full_name: %s, max_val: %u, has_vas %u\n"RESET, full_name, value, opt->has_value);

    return (opt);
}

/**
 *	@brief Update opt_str
 *	@param flag_c flag context
 *	@param c char to add
 *	@return 1 if success, 0 otherwise
*/
static s8 update_opt_str(FlagContext *flag_c, u8 c)
{
    char new_char[2] = {c, 0};
    if (flag_c->opt_str == NULL) {
        flag_c->opt_str = ft_strdup(new_char);
    } else {
        flag_c->opt_str = ft_strjoin_free(flag_c->opt_str, new_char, 'f');
    }
    if (!flag_c->opt_str) {
        ft_printf_fd(2, "Failed to allocate memory for opt_str\n");
        return (0);
    }
    return (1);
}

/**
 *	@brief Add flag option
 *	@param flag_c flag context
 *	@param c flag char
 *	@param flag_val flag value
 *	@param value max value accepted
 *	@param value_type type of value
 *	@param full_name full name of the flag
 *	@return 1 if success, 0 otherwise
*/
s8 add_flag_option(FlagContext *c, char* full_name, u32 flag_val, char flag_char) {
    OptNode *opt = NULL;
    s8 ret = 0;

    if (!c) {
        ft_printf_fd(2, "Invalid flag context\n");
        return (0);
    } 
    else if (search_exist_opt(c->opt_lst, is_same_char_opt, &flag_char)\
        || search_exist_opt(c->opt_lst, is_same_flag_val_opt, &flag_val)) {
        ft_printf_fd(2, RED"Opt char |%c| or flag val |%d| already present\n"RESET, flag_char, flag_val);
        return (0);
    }
    opt = create_opt_node(flag_char, flag_val, full_name);
    ft_lstadd_back(&c->opt_lst, ft_lstnew(opt));
    ret = update_opt_str(c, flag_char); 
    return (ret);
}

void free_optvalue(OptNode *opt, U_OptValue *val) {
	
	if ((opt->value_type > DECIMAL_VALUE)) {
		free(val->str);
	}
}

/**
 *	@brief Free opt node
 *	@param content content to free
*/
void free_opt_node(void *content)
{
    OptNode *opt = (OptNode *)content;
    if (opt) {
        if (opt->full_name) {
            free(opt->full_name);
        }
		for (t_list *val_lst = opt->val_lst; val_lst; val_lst = val_lst->next) {
			free_optvalue(opt, val_lst->content);
		}
		ft_lstclear(&opt->val_lst, free);
        free(opt);
    }
}

/**
 *	@brief Free flag context
 *	@param flag_c flag context
*/
void free_flag_context(FlagContext *flag_c)
{
    if (flag_c) {
		if (flag_c->opt_str) {
            free(flag_c->opt_str);
        }
        if (flag_c->opt_lst) {
            ft_lstclear(&flag_c->opt_lst, free_opt_node);
        }
        free(flag_c);
    }
}