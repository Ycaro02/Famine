#!/bin/bash

source ./rsc/sh/color.sh


rm_pid_log() {
	if [ -f "${1}" ]; then
		rm "${1}"
	fi
}

send_sigint() {
	PID=$1
	# display_color_msg ${YELLOW} "Sending SIGINT to pid: ${PID}"
	kill -2 ${PID} 2> /dev/null
}

send_sigint_all() {
	local to_found="${1}"
	display_color_msg ${YELLOW} "Sending SIGINT to all pid ..."
	PID_FOUND=$(ps | grep ${to_found} | awk '{print $1}')
	for pid in ${PID_FOUND}
	do
		send_sigint ${pid}
		sleep 0.05
	done
	sleep 0.1
	PID_FOUND=$(ps | grep ${to_found} | awk '{print $1}')
	if [ "${PID_FOUND}" == "" ]; then
		display_color_msg ${GREEN} "No pid found, all ${to_found} instance clean up"
	else
		display_color_msg ${RED} "Pid found: ${PID_FOUND}"
	fi
}

wait_and_display_log() {
    local file="${1}"
    local to_found="${2}"
	local to_wait="${3}"
	display_color_msg ${MAGENTA} "Waiting ${to_wait} sec, display ${1}"
    sleep ${to_wait}
	send_sigint_all ${to_found}
    cat ${file}
    rm ${file}
}