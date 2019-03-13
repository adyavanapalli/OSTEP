#!/usr/bin/env bash
# init.sh - gets submodules and runs any necessary start-up scripts.

# Get submodules.
git submodule init
git submodule update --recursive

# Run start-up scripts.
./scripts/get-homework.sh
