#!/usr/bin/env bash
# get-homework.sh - downloads and extracts all homework files on the OSTEP website.

ALL="all.tgz"
URL="http://www.cs.wisc.edu/~remzi/OSTEP/Homework/$ALL"

# Checking existence of wget.
command -v wget >/dev/null 2>&1 || { echo >&2 "Missing wget. Aborting."; exit 1; }

# Download and extract the `all.tgz` homework file.
wget "$URL"
tar zxvf "$ALL" -C third-party/homework-files/
rm "$ALL"

# Extract every individual homework file.
cd third-party/homework-files || exit
for folder in HW-*; do
(
    cd "$folder" || exit
    tar zxvf ./*.tgz
    rm -f ./*.tgz ./._*
)
done
