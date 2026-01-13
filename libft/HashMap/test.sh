#!/bin/bash

gcc hashMap_test.c HashMap.c ../libft.a ../list/linked_list.a -g\
	&& valgrind --leak-check=full ./a.out
rm -rf a.out
