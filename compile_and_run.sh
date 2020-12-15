#!/bin/sh

files=$(ls | grep '.cpp' | sort -V)

for file in $files; do
    binary=$(basename "$file" '.cpp')
    input=$(echo "$binary" | sed 's/.$/.input/')

    g++ -O2 -std=c++11 -Wall -Wextra -Wstrict-aliasing -pedantic -Werror -o "$binary" "$file"
    chmod +x "$binary"

    echo -n "${binary}: "
    time ./"$binary" < "$input"
done
