#!/bin/sh

GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

SRC=$HOME'/BB8/.clang_complete'
UPDATED=0

for dir in `find ~/BB8/src/ -type d`; do
    found=$(grep -l "$dir" $SRC)
    if [ ! "$found" ]; then
        echo "${GREEN}ADDING:${NC} $dir"
        echo $dir | sed 's/^/-I/g' >> $SRC
        UPDATED=$((UPDATED+1))
    fi
done

if test $UPDATED -eq 0; then
    echo "$SRC is already up to date."
else
    echo "      ${BLUE}UPDATED${NC} [$UPDATED] directories."
fi
