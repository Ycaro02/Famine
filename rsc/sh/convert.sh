#!/bin/bash

# $1 input	base
# $2 output base
# $3 number to convert

bc <<< "obase=${1};ibase=${2};${3}"