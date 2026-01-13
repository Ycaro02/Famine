#ifndef PARSE_FLAG_H
#define PARSE_FLAG_H 1

#include "../libft.h"


/* Message invalid option */
#define PARSE_FLAG_ERR_MSG              RED"%s: invalid option -- %s\nTry %s -h for more information\n"RESET

/* Message argument required for flag */
#define PARSE_FLAG_ERR_MSG_ARGS_REQ     RED"%s: option requires an argument -- %c\nTry %s -h for more information\n"RESET

/* Message wrong arguments for flag */
#define PARSE_FLAG_ERR_MSG_WRONG_ARGS   RED"%s: invalid argument -- %c don't accept [%s] as argument\nTry %s -h for more information\n"RESET


#define DEFAULT_MAX_VAL 50000U

#define CHAR_FORMAT		0U          /* short format for check_for_flag */
#define LONG_FORMAT		1U          /* long format for check_for_flag */

typedef enum opt_value_type {
	OPT_NO_VALUE=0U,	/* no value linked */
	DECIMAL_VALUE=1U,	/* decimal base for value */
	HEXA_VALUE=2U,		/* hexadecimal base for value */
	OCTAL_VALUE=3U,		/* octal vase for value */
	BINARY_VALUE=4U,	/* binary base for value */
	CHAR_VALUE=5U,		/* char value all string accepted*/
	CUSTOM_VALUE=6U,	/* Custom value, user must provide function pointer to parse it, return TRUE or 1 for accepted value, 0 or FALSE to reject it */
} E_OptValueType;

typedef enum opt_value_overrid {
	VALUE_OVERRID=0, /* Overrid last saved value */
	VALUE_NO_OVERRID=1, /* Don't overrid value (erorr if we specify the option two time) */
	VALUE_APPEND=2, /* Just append value in U_OptValue list */
} E_OptValueOverride;


// function pointer typedef for custom value parse, void pointer must contain OptNode pointer
typedef s8 (*CustomValParse)(void*, void *);

/* Error code for set_flag_value */
#define ERROR_SET_VALUE	0
#define SUCCESS_SET_VALUE 1
#define CANT_BE_OVERRID 2

typedef union uopt_val {
    uint32_t digit;
    char    *str;   
} U_OptValue;

typedef struct OptNode {
    char			*full_name;     /* full name opt */
    t_list			*val_lst;		/* list of U_OptValues enum for storing value */
    CustomValParse	parse;			/* Function pointer to parse custom data or override basic parse func, null if regular type and don't want to override */
	u32				flag_val;       /* flag value, used with bitwise to create application flag */
	u32				min_val;        /* min value for linked val, or strlen min for string store */
    u32				max_val;        /* max value for linked val, or strlen max for string store */
	u32				nb_stored_val;	/* Number of stored value */
    u8				flag_char;      /* char represent flag */
    u8				value_type;     /* value type */
    s8				multiple_val;   /* Accept multiple value or not */
    u8				has_value;      /* if value is linked */
	s8				add_value_after_parse; /* Bool il we need to add value after parse function (default TRUE)*/ 
}   OptNode;


// s8 add_flag_opt(FlagContext *c, char *full_name, u8 opt_char, u32 flag_val);

typedef enum e_FlagOptSet {
    EOPT_MAX_VAL = 0,
	EOPT_MIN_VAL = 1U,
    EOPT_VALUE_TYPE=2U,
    EOPT_MULTIPLE_VAL=3U,
	EOPT_PARSE_FUNC=4U,
	EOPT_ADD_VAL_AFTER_PARSE=5U,
} E_FlagOptSet ;

typedef struct flag_context {
    char		*prg_name;		/* program name */
	char        *opt_str;       /* full char opt */
    t_list      *opt_lst;       /* list of opt node */
    s8          error;
}   FlagContext;

/* parse cmd_line */
t_list  *extract_args(int argc, char **argv);

/****************************/
/*		Parse flag			*/
/****************************/

/**
 * @brief Init the flag context structure
 * @param argv pointer on argument
 * @return allocated flag context pointer, NULL for malloc error
*/
FlagContext *flag_context_init(char **argv);

/**
 * @brief Parse flag
 * @param argc number of argument
 * @param argv pointer on argument
 * @param flag_c pointer on flag context
 * @param error pointer on error
 * @return flags if valid, 0 otherwise and set error to -1
*/
u32     parse_flag(int argc, char **argv,FlagContext *flag_c, s8 *error);

/**
 * @brief Display flags
 * @param all_flag all flag char available
 * @param flags flags to display
*/
void    display_flags(char *all_flag, int flags);

/**
 * @brief get option value
 * @param opt_lst list of opt node
 * @param flag flag to check
 * @param to_find flag to find
 * @return value if found, NULL otherwise
*/
OptNode *get_opt_node(t_list *opt_lst, u32 flag, u32 to_find);

/**
 *	@brief Set flag, enable target flag_val in flags
 *	@param flags pointer on flags
 *	@param flag_val flag value to set
*/
void set_flag(u32 *flags, u32 flag_val);

/**
 *	@brief Unset flag, disable target flag_val in flags
 *	@param flags pointer on flags
 *	@param flag_val flag value to unset
*/
void unset_flag(u32 *flags, u32 flag_val);

/**
 *	@brief Check if flag_val is enable in flags
 *	@param flags flags to check
 *	@param flag_val flag value to check
 *	@return 1 if flag_val is enable in flags, 0 otherwise
*/
s8  has_flag(u32 flags, u32 flag_val);

/* has flag wrapper */
s8  flag_already_present(u32 flags, u32 flag_val);

/**
 * @brief Reverse flag value
 * @param flags pointer on flags to be modified
 * @param flag_val flag value to reverse
*/
void	reverse_flag(u32 *flags, u32 flag_val);


/****************************/
/*		Handle Option		*/
/****************************/

/**
 *	@brief Add flag option
 *	@param c flag context
 *	@param full_name full name of the flag
 *	@param flag_val the power 2 flag value
 *	@param flag_char the flag char
 *	@return 1 if success, 0 otherwise
*/
s8 add_flag_option(FlagContext *c, char* full_name, u32 flag_val, char flag_char);

// s8 set_flag_option(FlagContext *c, u32 flag_val, E_FlagOptSet opt, void *value);
s8 set_flag_option(FlagContext *c, u32 flag_val, E_FlagOptSet opt_to_set, ...);

/**
 * @brief Display option list for debug
 * @param flag_c flag context
 * @param opt_lst list of opt node
*/
void display_option_list(FlagContext flag_c);

/**
 *	@brief Free flag context
 *	@param flag_c flag context
*/
void    free_flag_context(FlagContext *flag_c);

/* explicit compare function for search exist opt */
s8	is_same_full_name(void *node, void *data);
s8  is_same_char_opt(void *content, void *c);
s8  is_same_flag_val_opt(void *content, void *value);

/**
 * @brief Search for exist opt
 * @param opt_lst list of opt node
 * @param cmp compare function
 * @param data data to compare
 * @return opt_node if found, NULL otherwise
*/
void	*search_exist_opt(t_list *opt_lst, s8 (cmp()), void *data);

/**
 * @brief get opt values
 * @param opt_lst list of opt node
 * @param flag flag to check
 * @param to_find flag to find
 * @return t_list of U_opt_value if found, NULL otherwise
 */
t_list *get_opt_value(t_list *opt_lst, u32 flag, u32 to_find);

/**
 * @brief free optValue union
 * @param opt opt node
 * @param val value to free
 */
void free_optvalue(OptNode *opt, U_OptValue *val);

/**
 * @brief Alloc OptValue Unions
 * @return allocated U_OptValue pointer
*/
U_OptValue *opt_val_new();


s8 insert_digit_val(OptNode* opt, U_OptValue *opt_val, char *str);
s8 insert_string_val(OptNode *opt, U_OptValue *opt_val, char *str);

#endif /* PARSE_FLAG_H */