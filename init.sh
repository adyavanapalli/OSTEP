#!/usr/bin/env bash
# init.sh - gets submodules and runs any necessary start-up scripts.

git submodule update --recursive
./scripts/get-homework.sh
