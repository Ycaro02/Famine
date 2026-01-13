#!/bin/bash

source ./rsc/sh/bash_log.sh

if [ $# -ne 1 ]; then
    echo "Usage: $0 <root_famine_dir_lst>"
    echo "Example: $0 '/path/to/dir1 /path/to/dir2'"
    exit 1
fi

LOG_LEVEL=INFO

EXPECTED_SIGNATURE="Famine version 1.0 (c)oded by nfour-kbutor-b"

TESTER_VERBOSE_LOG="/tmp/test-log.txt"

function famine_tester() {
    local root_famine_dir_lst=${1}
    
    for dir in ${root_famine_dir_lst}; do
        if [ ! -d "${dir}" ]; then
            log E "Directory ${dir} does not exist."
            return 1
        fi
        log I "Scanning directory: ${dir}"
        local elf_file_lst=$(find ${dir} -type f -exec file {} \; | grep ELF | awk -F : '{print $1}')
        log I "Found $(echo "${elf_file_lst}" | wc -l) ELF files in ${dir}."
    
        for f in ${elf_file_lst}; do
            local signature_output=$(strings ${f} | grep "${EXPECTED_SIGNATURE}")
            if [[ ! -z "${signature_output}" ]] && [[ ${signature_output} == "${EXPECTED_SIGNATURE}" ]]; then
                log I "File ${f} signed" 2>> ${TESTER_VERBOSE_LOG}
            else 
                log E "File ${f} NOT signed [${signature_output}] != [${EXPECTED_SIGNATURE}]"
                exit 1
            fi
        done
        log I "All ELF files in ${dir} are correctly signed."
    done
}

log I "Setting up test directories..."
rm -rf /tmp/test /tmp/test2
mkdir -p /tmp/test2 /tmp/test/subdir/nested
cp /bin/* /tmp/test/ && \
    cp /bin/* /tmp/test2/ && \
    cp /bin/* /tmp/test/subdir/ && \
    cp /bin/* /tmp/test/subdir/nested/

log I "Verbose log will be saved to: ${TESTER_VERBOSE_LOG}"
rm -f ${TESTER_VERBOSE_LOG}

make -s -j
log I "Starting Famine tester on directories: ${1}"
log I "Expected signature: ${EXPECTED_SIGNATURE}"
log I "----------------------------------------"
log I "Running Famine binary..."
./Famine
log I "----------------------------------------"
log I "Checking ELF files signatures..."
famine_tester "${1}"
