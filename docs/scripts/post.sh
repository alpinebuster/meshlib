#!/bin/bash

# Define default values if arguments are not provided
TARGET_DIR="${1:-MeshLib/local}"
URL_PREFIX="${2:-https://meshlib.io/documentation}"

BASE_DIR=$(realpath $(dirname "$0"))

"$BASE_DIR/update_logo_link.sh" "$TARGET_DIR/html" "https://meshlib.io/"

# Conditionally run update_canonical.sh if TARGET_DIR is not "MeshLib/dev"
if [ "$TARGET_DIR" == "MeshLib" ]; then
  "$BASE_DIR/update_canonical.sh" "$TARGET_DIR/html" "$URL_PREFIX"
  "$BASE_DIR/remove_noindex.sh" "$TARGET_DIR/html" "whitelist.txt"
fi
