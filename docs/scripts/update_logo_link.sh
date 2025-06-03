#!/bin/sh

# Configuration variables
HTML_DIR="$1"
URL_PREFIX="$2"

# Check if both arguments are provided
if [ -z "$HTML_DIR" ] || [ -z "$URL_PREFIX" ]; then
  echo "Usage: $0 HTML_DIR URL_PREFIX"
  exit 1
fi

# Function to update <img alt="Logo" src="favicon.ico"> to <a href="URL_PREFIX"><img alt="Logo" src="favicon.ico"></a>
update_logo_link() {
  file_path="$1"

  # Use sed to update the logo link link tag
  sed -i -E "s|<img alt=\"Logo\" src=\"favicon.ico\"/>|<a href=\"$URL_PREFIX\"><img alt=\"Logo\" src=\"favicon.ico\"/></a>|" "$file_path"
  echo "Updated Logo link in: $file_path"
}

# Find all .html files and update logo link
find "$HTML_DIR" -type f -name "*.html" | while read -r file; do
  update_logo_link "$file"
done