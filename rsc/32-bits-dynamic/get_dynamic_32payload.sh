#!/bin/bash

mkdir -p obj
nasm -f elf32 src/woody/asm/decrypt_data_exec_32.s -o obj/decrypt_data_exec_32.o
gcc -m32 rsc/32-bits-dynamic/main32_get_payload.c obj/decrypt_data_exec_32.o libft/libft.a -o rsc/32-bits-dynamic/get_opcode32

./rsc/32-bits-dynamic/get_opcode32

rm ./rsc/32-bits-dynamic/get_opcode32