# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    color.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfour <nfour@student.42angouleme.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 16:54:27 by nfour             #+#    #+#              #
#    Updated: 2024/04/11 16:54:32 by nfour            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Colors
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
MAGENTA="\e[35m"
CYAN="\e[36m"
LIGHT_GRAY="\e[37m"
GRAY="\e[90m"
LIGHT_RED="\e[91m"
LIGHT_GREEN="\e[92m"
LIGHT_YELLOW="\e[93m"
LIGHT_BLUE="\e[94m"
LIGHT_MAGENTA="\e[95m"
LIGHT_CYAN="\e[96m"
WHITE="\e[97m"
RESET="\e[0m"

display_color_msg() {
	COLOR=$1
	MSG=$2
	echo -e "${COLOR}${MSG}${RESET}"
}

display_double_color_msg () {
	COLOR1=$1
	MSG1=$2
	COLOR2=$3
	MSG2=$4
	echo -e "${COLOR1}${MSG1}${RESET}${COLOR2}${MSG2}${RESET}"
}
