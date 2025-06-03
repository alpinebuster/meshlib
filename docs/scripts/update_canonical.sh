#!/bin/sh

# Configuration variables
HTML_DIR="$1"
URL_PREFIX="$2"

# Check if both arguments are provided
if [ -z "$HTML_DIR" ] || [ -z "$URL_PREFIX" ]; then
  echo "Usage: $0 HTML_DIR URL_PREFIX"
  exit 1
fi

# Function to update <link rel="canonical"> tag
update_canonical() {
  file_path="$1"
  relative_path="${file_path#$HTML_DIR/}"
  canonical_url="${URL_PREFIX}/${relative_path}"

  # Use sed to update the canonical link tag
  sed -i -E "s|<link rel=\"canonical\" href=\"[^\"]*\" />|<link rel=\"canonical\" href=\"$canonical_url\" />|" "$file_path"
  echo "Updated canonical link in: $file_path"
}

# Find all .html files and update canonical link
find "$HTML_DIR" -type f -name "*.html" | while read -r file; do
  update_canonical "$file"
done