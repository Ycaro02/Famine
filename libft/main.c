#include "libft.h"
#include "parse_flag/parse_flag.h"

enum flag_enum {
	DIGIT_FLAG=1,
	STRING_FLAG=2,
	HEXA_FLAG=4,
	OCTAL_FLAG=8,
	KUSTOM_FLAG=16,
};

void verify_decimal_flag(FlagContext *c, u32 flag, u32 *wanted_val, u32 nb_wanted_val) {

	OptNode *opt = get_opt_node(c->opt_lst, flag, DIGIT_FLAG);

	u32 i = 0;

	if (!opt) {
		ft_printf_fd(1, "No opt found for decimal\n");
		return;
	}

	for (t_list *val_lst = opt->val_lst; val_lst; val_lst = val_lst->next) {
		U_OptValue *val = val_lst->content;
		if (val->digit != wanted_val[i]) {
			ft_printf_fd(2, "Error decimal %d: wanted %d, got %d\n", i, wanted_val[i], val->digit);
		}
		i++;
	}

	if (i != nb_wanted_val) {
		ft_printf_fd(2, "Error: wanted %d, got %d\n", nb_wanted_val, i);
	}
	// ft_printf_fd(2, "All test passed for '%c'\n", opt->flag_char);
}

void verify_string_flag(FlagContext *c, u32 flag, char **wanted_val, u32 nb_wanted_val, u32 wanted_flag) {
	OptNode *opt = get_opt_node(c->opt_lst, flag, wanted_flag);
	u32 i = 0;

	if (!opt) {
		ft_printf_fd(1, "No opt found for string\n");
		return;
	}


	for (t_list *val_lst = opt->val_lst; val_lst; val_lst = val_lst->next) {
		U_OptValue *val = val_lst->content;
		if (ftlib_strcmp(val->str, wanted_val[i]) != 0) {
			ft_printf_fd(2, "Error string %d: wanted %s, got %s\n", i, wanted_val[i], val->str);
		}
		i++;
	}
	if (i != nb_wanted_val) {
		ft_printf_fd(2, "Error: wanted %d, got %d\n", nb_wanted_val, i);
	}
}

s8 test_parse(void *c) {
	(void)c;
	ft_printf_fd(1, "Call test_parse OK\n");
	return (TRUE);
}

void init_flag_context(FlagContext *c, u8 value_handling) {
	add_flag_option(c, "count", DIGIT_FLAG, 'c');
	set_flag_option(c, DIGIT_FLAG, EOPT_VALUE_TYPE, DECIMAL_VALUE);
	set_flag_option(c, DIGIT_FLAG, EOPT_MAX_VAL, 100);
	set_flag_option(c, DIGIT_FLAG, EOPT_MULTIPLE_VAL, value_handling);
	set_flag_option(c, DIGIT_FLAG, EOPT_MIN_VAL, 2);

	add_flag_option(c, "string", STRING_FLAG, 's');
	set_flag_option(c, STRING_FLAG, EOPT_VALUE_TYPE, CHAR_VALUE);	
	set_flag_option(c, STRING_FLAG, EOPT_MAX_VAL, 100);
	set_flag_option(c, STRING_FLAG, EOPT_MULTIPLE_VAL, value_handling);
	set_flag_option(c, STRING_FLAG, EOPT_MIN_VAL, 2);

	add_flag_option(c, "hexa-val", HEXA_FLAG, 'a');
	set_flag_option(c, HEXA_FLAG, EOPT_VALUE_TYPE, HEXA_VALUE);	
	set_flag_option(c, HEXA_FLAG, EOPT_MAX_VAL, 100);
	set_flag_option(c, HEXA_FLAG, EOPT_MULTIPLE_VAL, value_handling);

	add_flag_option(c, "octal", OCTAL_FLAG, 'o');
	set_flag_option(c, OCTAL_FLAG, EOPT_VALUE_TYPE, OCTAL_VALUE);	
	set_flag_option(c, OCTAL_FLAG, EOPT_MAX_VAL, 100);
	set_flag_option(c, OCTAL_FLAG, EOPT_MULTIPLE_VAL, value_handling);

}


// void call_tester() {
int call_tester( int argc, char **argv, u32 *wanted_digit, u32 nb_wanted_digit, char **wanted_str, u32 nb_wanted_str, char **wanted_hexa, u32 nb_wanted_hexa, char **wanted_octal, u32 nb_wanted_octal, u8 value_handling) {
	FlagContext *c = flag_context_init(argv);

	init_flag_context(c, value_handling);

	/* call flag parser */
	u32 flag = parse_flag(argc, argv, c, &c->error);
	if (c->error) {
		// ft_printf_fd(2, YELLOW"Parse flag error\n"RESET);
		free_flag_context(c);
		return (0);
	}
	verify_decimal_flag(c, flag, wanted_digit, nb_wanted_digit);
	verify_string_flag(c, flag, wanted_str, nb_wanted_str, STRING_FLAG);
	verify_string_flag(c, flag, wanted_hexa, nb_wanted_hexa, HEXA_FLAG);

	if (nb_wanted_octal > 0) {
		verify_string_flag(c, flag, wanted_octal, nb_wanted_octal, OCTAL_FLAG);
	}


	// debug display all flag and val here
	// display_option_list(*c);
	// debug display all flag and val here

	free_flag_context(c);
	return (1);
}


void test1_append() {
	char *argv[] = {"./test", "--count", "10", "-c", "20", "-s", "string1", "-c", "30", "-s", "KOALA", "-a", "ffaa", "-a", "01234fa", "-c", "40", "-o", "0127"};
	int argc = (sizeof(argv) / sizeof(char *)); 
	u32 wanted_digit[] = {10, 20, 30, 40};
	char *wanted_str[] = { "string1", "KOALA"}; 
	char *wanted_hexa[] = { "ffaa", "01234fa" };
	char *wanted_octal[] = {"0127"};

	u32 nb_digit = sizeof(wanted_digit) / sizeof(u32);
	u32 nb_str = sizeof(wanted_str) / sizeof(char *);
	u32 nb_hexa = sizeof(wanted_hexa) / sizeof(char *);
	u32 nb_octal = sizeof(wanted_octal) / sizeof(char *);

	int ret = call_tester(argc, argv, wanted_digit, nb_digit, wanted_str, nb_str, wanted_hexa, nb_hexa, wanted_octal, nb_octal, VALUE_APPEND);
	if (ret != 1) {
		ft_printf_fd(1, RED"Test error\n"RESET);
	} else {
		ft_printf_fd(1, GREEN"Test 1 append success\n"RESET);
	}
}

void test2_append() {
	char *argv[] = {"./test", "-c", "10", "-c2", "-sfoo", "-c", "3", "-s", "bar", "-adead01", "-a", "beef", "-c4"};
	int argc = (sizeof(argv) / sizeof(char *));
	u32 wanted_digit[] = {10, 2, 3, 4};
	char *wanted_str[] = {"foo", "bar"};
	char *wanted_hexa[] = {"dead01", "beef"};

	u32 nb_digit = sizeof(wanted_digit) / sizeof(u32);
	u32 nb_str = sizeof(wanted_str) / sizeof(char *);
	u32 nb_hexa = sizeof(wanted_hexa) / sizeof(char *);

	int ret = call_tester(argc, argv, wanted_digit, nb_digit, wanted_str, nb_str, wanted_hexa, nb_hexa, NULL, 0,VALUE_APPEND);
	if (ret != 1) {
		ft_printf_fd(1, RED"Test error\n"RESET);
	} else {
		ft_printf_fd(1, GREEN"Test 2 append success\n"RESET);
	}
}


void test1_override() {
	char *argv[] = {"./test", "--count", "10", "-c", "20", "-s", "string1", "-c", "30", "-s", "KOALA", "-a", "ffaa", "-a", "01234fa", "-c", "40"};
	int argc = (sizeof(argv) / sizeof(char *)); 
	u32 wanted_digit[] = {40};
	char *wanted_str[] = {"KOALA"}; 
	char *wanted_hexa[] = {"01234fa"};

	u32 nb_digit = 1;
	u32 nb_str = 1;
	u32 nb_hexa = 1;

	int ret = call_tester(argc, argv, wanted_digit, nb_digit, wanted_str, nb_str, wanted_hexa, nb_hexa, NULL, 0, VALUE_OVERRID);
	if (ret != 1) {
		ft_printf_fd(1, RED"Test error\n"RESET);
	} else {
		ft_printf_fd(1, GREEN"Test 1 override success\n"RESET);
	}
}

void test2_override() {
	char *argv[] = {"./test", "--count", "10", "-c", "20", "-s", "string1", "-c", "30", "-s", "KOALA", "-a", "ffaa", "-add", "-a", "01234fa", "-aff", "-c40", "-stest_last"};
	int argc = (sizeof(argv) / sizeof(char *)); 
	u32 wanted_digit[] = {40};
	char *wanted_str[] = {"test_last"}; 
	char *wanted_hexa[] = {"ff"};

	u32 nb_digit = 1;
	u32 nb_str = 1;
	u32 nb_hexa = 1;

	int ret = call_tester(argc, argv, wanted_digit, nb_digit, wanted_str, nb_str, wanted_hexa, nb_hexa,NULL, 0, VALUE_OVERRID);
	if (ret != 1) {
		ft_printf_fd(1, RED"Test error\n"RESET);
	} else {
		ft_printf_fd(1, GREEN"Test 2 override success\n"RESET);
	}
}

void test1_no_override() {
	char *argv[] = {"./test", "--count", "10", "-slol", "-aff", "-aAAb"};
	int argc = (sizeof(argv) / sizeof(char *)); 
	u32 wanted_digit[] = {10};
	char *wanted_str[] = {"lol"}; 
	char *wanted_hexa[] = {"ff"};

	u32 nb_digit = 1;
	u32 nb_str = 1;
	u32 nb_hexa = 1;

	int ret = call_tester(argc, argv, wanted_digit, nb_digit, wanted_str, nb_str, wanted_hexa, nb_hexa, NULL, 0,VALUE_NO_OVERRID);
	if (ret == 0) {
		ft_printf_fd(1, GREEN"Test Value can't be overrid return error\n"RESET);
	} else {
		ft_printf_fd(1, RED"Test Value can't be overrid no error\n"RESET);
	}
}


void test1_invalid_flag() {
	char *argv[] = {"./test", "--count", "10", "-slol", "-aff", "-c20", "-k", "testK"};
	int argc = (sizeof(argv) / sizeof(char *)); 
	u32 wanted_digit[] = {10};
	char *wanted_str[] = {"lol"}; 
	char *wanted_hexa[] = {"ff"};

	u32 nb_digit = 1;
	u32 nb_str = 1;
	u32 nb_hexa = 1;

	int ret = call_tester(argc, argv, wanted_digit, nb_digit, wanted_str, nb_str, wanted_hexa, nb_hexa,NULL, 0, VALUE_APPEND);
	if (ret == 0) {
		ft_printf_fd(1, GREEN"Test invalid flag return error\n"RESET);
	} else {
		ft_printf_fd(1, RED"Test invalid flag no error\n"RESET);
	}
}


int main (int argc, char **argv) {

	test1_append();
	test2_append();
	test1_override();
	test2_override();
	test1_no_override();
	// test_input(argc, argv);
	test1_invalid_flag();
	return 0;
}