#!/bin/bash

gcc bitshift_test.c && ./a.out; rm a.out
gcc test_fast_strcmp.c ../libft.a && ./a.out; rm a.out
