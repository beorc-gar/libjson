#!/bin/sh

for file in tests/*.json; do
    ./libjsontest $file > testout/got/$file

    if cmp --silent testout/got/$file testout/exp/$file; then
        echo "\033[0;32m$file\033[0m"
    else
        echo "\033[0;31m$file\033[0m"
    fi
done