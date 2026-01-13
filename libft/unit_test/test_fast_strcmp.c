#include <assert.h>

#include "../libft.h"

void test_ft_strcmp(void)
{
    assert(ft_strcmp("hello", "hello") == 0);

    assert(ft_strcmp("abc", "abcd") == ('\0' - 'd'));

    assert(ft_strcmp("abcd", "abc") == ('d' - '\0'));

    assert(ft_strcmp("foo", "bar") == ('f' - 'b'));

    assert(ft_strcmp("", "nonempty") == ('\0' - 'n'));
    assert(ft_strcmp("nonempty", "") == ('n' - '\0'));

    assert(ft_strcmp("", "") == 0);

	const char *long_str1 = "This is a very long string used for testing purposes. "
                            "It contains multiple sentences and is designed to test "
                            "the performance and correctness of the ft_strcmp function.";
    const char *long_str2 = "This is a very long string used for testing purposes. "
                            "It contains multiple sentences and is designed to test "
                            "the performance and correctness of the ft_strcmp function.";
    assert(ft_strcmp(long_str1, long_str2) == 0);

    const char *long_str3 = "This is a very long string used for testing purposes. "
                            "It contains multiple sentences and is designed to test "
                            "the performance and correctness of the ft_strcmp function.";
    const char *long_str4 = "This is a very long string used for testing purposes. "
                            "It contains multiple sentences and is designed to test "
                            "the performance and correctness of the ft_strcmp function. Extra characters.";
    assert(ft_strcmp(long_str3, long_str4) == ('\0' - ' '));

    const char *long_str5 = "This is a very long string used for testing purposes. "
                            "It contains multiple sentences and is designed to test "
                            "the performance and correctness of the ft_strcmp function. Extra characters.";
    const char *long_str6 = "This is a very long string used for testing purposes. "
                            "It contains multiple sentences and is designed to test "
                            "the performance and correctness of the ft_strcmp function.";
    assert(ft_strcmp(long_str5, long_str6) == (' ' - '\0'));

    const char *long_str7 = "This is a very long string used for testing purposes. "
                            "It contains multiple sentences and is designed to test "
                            "the performance and correctness of the ft_strcmp function.";
    const char *long_str8 = "Another very long string used for testing purposes. "
                            "It contains multiple sentences and is designed to test "
                            "the performance and correctness of the ft_strcmp function.";
    assert(ft_strcmp(long_str7, long_str8) == ('T' - 'A'));
	ft_printf_fd(1, GREEN"All tests passed for %s\n"RESET, __func__);
}

void test_fast_strlen(void)
{
	assert(fast_strlen("hello") == 5);
	assert(fast_strlen("abc") == 3);
	assert(fast_strlen("abcd") == 4);
	assert(fast_strlen("foo") == 3);
	assert(fast_strlen("") == 0);

	const char *long_str = "This is a very long string used for testing purposes. "
							"It contains multiple sentences and is designed to test "
							"the performance and correctness of the fast_strlen function.";
	assert(fast_strlen(long_str) == 169);
	ft_printf_fd(1, GREEN"All tests passed for %s\n"RESET, __func__);
}

void test_fast_strcpy(void)
{
	char dst[100];
	assert(fast_strcpy(dst, "hello") == dst);
	assert(ft_strcmp(dst, "hello") == 0);

	assert(fast_strcpy(dst, "abc") == dst);
	assert(ft_strcmp(dst, "abc") == 0);

	assert(fast_strcpy(dst, "abcd") == dst);
	assert(ft_strcmp(dst, "abcd") == 0);

	assert(fast_strcpy(dst, "foo") == dst);
	assert(ft_strcmp(dst, "foo") == 0);

	assert(fast_strcpy(dst, "") == dst);
	assert(ft_strcmp(dst, "") == 0);

	char dst2[200];

	const char *long_str = "This is a very long string used for testing purposes. "
							"It contains multiple sentences and is designed to test "
							"the performance and correctness of the fast_strcpy function.";
	assert(fast_strcpy(dst2, long_str) == dst2);
	assert(ft_strcmp(dst2, long_str) == 0);
	ft_printf_fd(1, GREEN"All tests passed for %s\n"RESET, __func__);
}

void test_fast_bzero(void)
{
	char buffer[100];
	fast_bzero(buffer, 100);
	for (int i = 0; i < 100; i++)
	{
		assert(buffer[i] == 0);
	}
	ft_printf_fd(1, GREEN"All tests passed for %s\n"RESET, __func__);

	char buffer2[4537];

	fast_bzero(buffer2, 4537);
	for (int i = 0; i < 4537; i++)
	{
		assert(buffer2[i] == 0);
	}

	char buffer3[1];

	fast_bzero(buffer3, 1);
	assert(buffer3[0] == 0);

	char buffer4[1024];

	fast_bzero(buffer4, 1024);
	for (int i = 0; i < 1024; i++)
	{
		assert(buffer4[i] == 0);
	}

	char buffer5[1025];

	fast_bzero(buffer5, 1025);
	for (int i = 0; i < 1025; i++)
	{
		assert(buffer5[i] == 0);
	}

	ft_printf_fd(1, GREEN"All tests passed for %s\n"RESET, __func__);

}

int main(void)
{
    test_ft_strcmp();
	test_fast_strlen();
	test_fast_strcpy();
	test_fast_bzero();
    return 0;
}