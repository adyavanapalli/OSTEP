#!/usr/bin/env bash
# get-homework.sh - downloads and extracts all homework files on the OSTEP website.

ALL="all.tgz"
URL="http://www.cs.wisc.edu/~remzi/OSTEP/Homework/$ALL"
echo "Attempting to download homework files from: $URL"

# Checking existence of wget.
command -v wget >/dev/null 2>&1 || { echo >&2 "Missing wget. Aborting."; exit 1; }

# Download and extract `all.tgz` homework file.
wget "$URL"
tar zxvf "$ALL" -C homework/
rm "$ALL"

# Extract every individual homework file.
cd homework || exit
for folder in HW-*; do
(
    cd "$folder" || exit
    tar zxvf ./*.tgz
    rm -f ./*.tgz ./._*
)
done
cd .. || exit
