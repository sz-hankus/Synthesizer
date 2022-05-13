#!/bin/bash

printf "Starting SFML instalation...\n"

if [[ -d SFML ]]; then
    printf "SFML directory already exists. Exiting.\n"
    exit 1
fi

printf "Creating SFML directory..."
mkdir SFML
printf " Done\n"

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        printf "GNU/Linux OS detected\n"
        download_url="https://www.sfml-dev.org/files/SFML-2.5.1-linux-gcc-64-bit.tar.gz"
elif [[ "$OSTYPE" == "darwin"* ]]; then
        printf "MacOS detected\n"
        download_url="https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz"
else
    printf "Unknown operating system. Exiting\n"
    exit 2
fi


printf "Download started...\n"
wget -qO SFML.tar.gz "$download_url"
if [[ "$?" != 0 ]]; then
    printf "Download unsuccesful. Exiting\n"
    exit 3
fi
printf "Download complete.\n"

tar -xzf SFML.tar.gz -C ./SFML --strip-components=1

rm SFML.tar.gz

printf "Installation complete.\n"