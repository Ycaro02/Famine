#!/bin/bash

# colors
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
MAGENTA="\e[35m"
CYAN="\e[36m"
GRAY="\e[90m"
L_GRAY="\e[37m"
L_RED="\e[91m"
L_GREEN="\e[92m"
L_YELLOW="\e[93m"
L_BLUE="\e[94m"
L_MAGENTA="\e[95m"
L_CYAN="\e[96m"
WHITE="\e[97m"
RESET="\e[0m"

display_color_msg() {
	local color=$1
	local msg=$2
	echo -e "${color}${msg}${RESET}"
}

display_double_color_msg () {
	local color1=$1
	local msg1=$2
	local color2=$3
	local msg2=$4
	echo -e "${color1}${msg1}${RESET}${color2}${msg2}${RESET}"
}

LOG_LVL_ARRAY=("ERROR" "WARNING" "INFO" "DEBUG")
LOG_LVL_VAL_ARRAY=("E" "W" "I" "D")

is_correct_log_level() {
    local is_valid="false"

    for valid_level in "${LOG_LVL_ARRAY[@]}"; do
        if [[ "${LOG_LEVEL}" == "${valid_level}" ]]; then
            is_valid="true"
            break
        fi
    done
    echo -n "${is_valid}"
}

check_log_level() {
    local level=${1}
    local display_log="false"
    
    local is_valid_level=$(is_correct_log_level)

    if [[ -z ${LOG_LEVEL} ]] || [[ ${is_valid_level} == "false" ]]; then
        # echo -e "${YELLOW}Warning:${RESET} LOG_LEVEL is not set or invalid, defaulting to INFO level" >&2
        LOG_LEVEL="INFO"
    fi

    local current_level_index=-1
    local config_level_index=-1

    for i in "${!LOG_LVL_VAL_ARRAY[@]}"; do
        if [[ "${level}" == "${LOG_LVL_VAL_ARRAY[$i]}" ]]; then
            current_level_index=$i
        fi
        if [[ "${LOG_LEVEL}" == "${LOG_LVL_ARRAY[$i]}" ]]; then
            config_level_index=$i
        fi
    done

    if [[ $current_level_index -le $config_level_index ]] || [[ "${level}" == "E" ]]; then
        display_log="true"
    fi

    echo -n "${display_log}"

}



# D for log DEBUG
# I for log info
# W for log WARNING
# E for log ERROR
log() {
	local level=${1}
	local msg="${2}"
	local date_str=${3}


	if [[ ! -z ${date_str} ]]; then
		date_str="${date_str} "
	fi


    local display_log=$(check_log_level ${level})

    if [[ ${display_log} == "false" ]]; then
        return
    fi

	case ${level} in

		"D")
			echo -e "${date_str}${CYAN}[ DBG ]${RESET} ${msg}" >&2
		;;

		"I")
			echo -e "${date_str}${GREEN}[ INF ]${RESET} ${msg}" >&2
			;;

		"W")
			echo -e "${date_str}${YELLOW}[ WAR ]${RESET} ${msg}" >&2
		;;

		"E")
			echo -e "${date_str}${RED}[ ERR ]${RESET} ${msg}" >&2
		;;

		*)
			echo -e "${date_str}${RED}Unknow level: ${msg} ${RESET}" >&2
    	;;
	esac

}

log_date() {
	local level=${1}
	local msg="${2}"
	local date_str=$(date +"%Y/%m/%d %H:%M:%S")

	log ${level} "${msg}" ${MAGENTA}"[ ${date_str} ]"${RESET}
}
