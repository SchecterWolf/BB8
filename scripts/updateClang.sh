#!/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color

SRC=$HOME'/BB8/.clang_complete'
UPDATED=0

declare -a aFileIn
declare -a aFileOut
mapfile -t aFileIn < $SRC

# Remove directories that dont exist anymore
for line in "${aFileIn[@]}"
do
    new=${line#"-I"}
    if [ -e $new ]; then
        aFileOut+=($line)
    else
        echo -e "${RED}REMOVING:${NC} $new"
    fi
done

# Write back the directories that do still exist
/usr/bin/truncate $SRC --size 0
for line in "${aFileOut[@]}"
do
    echo -e $line >> $SRC
done

# Add in new directories
for dir in `find ~/BB8/src/ -type d`; do
    found=$(grep -l "$dir" $SRC)
    if [ ! "$found" ]; then
        echo -e "${GREEN}ADDING:${NC}   $dir"
        echo $dir | sed 's/^/-I/g' >> $SRC
        UPDATED=$((UPDATED+1))
    fi
done

if test $UPDATED -eq 0; then
    echo "$SRC is already up to date."
else
    echo -e "      ${BLUE}UPDATED${NC} [$UPDATED] directories."
fi
