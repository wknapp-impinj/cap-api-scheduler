#!/usr/bin/env bash
set -eu

cd $(dirname $(realpath $0))

ETK_ROOT_PATH=$(realpath ../..) cap/build.sh "$@"