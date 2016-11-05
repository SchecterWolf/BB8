#!/bin/bash

# Target name
TARGET="BB-Boot"

# x86-linux build
LOC="target/x86-linux/"

PROG=0
CONFIG="Intellex-BB.conf"
if [ ! -z "$1" ]
then
    PROG=$1
    if [ ! -z "$2" ]
    then
        CONFIG=$2
    fi
else
    echo ''
    echo 'Select run mode:'
    echo '1) Run normally'
    echo '2) Run with GDB'
    echo '3) Run with Valgrind'

    read PROG
fi

# Valgrind flags
VALGRIND="--trace-children=yes --num-callers=50 --tool=memcheck --leak-check=full --track-origins=yes -v"

case $PROG in
    1) ${LOC}${TARGET} -c $CONFIG
        ;;
    2) /usr/bin/gdb ${LOC}${TARGET}
        ;;
    3) /usr/bin/valgrind $VALGRIND ${LOC}${TARGET} -c $CONFIG > BB.vlgd 2>&1
esac
