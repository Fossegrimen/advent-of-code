#!/bin/sh

files=$(ls | grep '.cpp' | sort -V)

for file in $files; do
    binary=$(basename "$file" '.cpp')
    input=$(echo "$binary" | sed 's/.$/.input/')

    g++ -std=c++11 -O3 -Ofast -Wall -Wextra -Wstrict-aliasing -pedantic -Werror -o "$binary" "$file"
    chmod +x "$binary"

    echo -n "${binary}: "
    time ./"$binary" < "$input"
done
