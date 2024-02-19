#!/bin/bash

buildDir="build"
executable="Techhi"

if [ ! -d "$buildDir" ]; then
    mkdir -p "$buildDir"
    echo "Build directory created: $buildDir"
fi

cmake -S . -B "$buildDir"
make -C "$buildDir"

if [ -x "$buildDir/$executable" ]; then
    clear
    echo -e "Running $executable...\n"
    ./"$buildDir/$executable"
else
    echo "Error: $executable not found or not executable"
    exit 1
fi
