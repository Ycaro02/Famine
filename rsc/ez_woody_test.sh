#!/bin/bash

make bonus

export FAMINE_ROOT_PATH="/tmp/woody_test"
export FAMINE_WOODY_ENABLE="true"

rm -rf /tmp/woody_test
mkdir -p /tmp/woody_test

cp /bin/ls /tmp/woody_test/ls_original
gcc -m32 rsc/main32.c -o /tmp/woody_test/main32

echo "=== Running ./Famine $1 $2 \"$3\" ==="
./Famine $1 $2 "$3" > woody_test.log 2>&1

echo "=== Testing woody executable with ls_original ==="
/tmp/woody_test/ls_original

echo "=== Testing woody executable with main32 ==="
/tmp/woody_test/main32