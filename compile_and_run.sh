#!/bin/sh

files=$(ls *'.cpp')

for file in $files; do
    binary=$(basename "$file" '.cpp')
    input=$(echo "$binary" | sed 's/.$/.input/')

    g++ -O2 -o "$binary" "$file"
    chmod +x "$binary"

    echo -n "${binary}: "
    ./"$binary" < "$input"
done
