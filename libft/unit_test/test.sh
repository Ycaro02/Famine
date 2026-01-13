#!/bin/bash

gcc bitshift_test.c && ./a.out; rm a.out
gcc test_ft_strcmp.c ../libft.a && ./a.out; rm a.out
