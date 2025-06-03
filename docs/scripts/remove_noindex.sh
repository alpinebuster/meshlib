#!/bin/sh

# Configuration variables
HTML_DIR="$1"
WHITE_LIST="$2"

# Check if both arguments are provided
if [ -z "$HTML_DIR" ] || [ -z "$WHITE_LIST" ]; then
  echo "Usage: $0 HTML_DIR WHITE_LIST"
  exit 1
fi

# Function to remove <meta name="robots" content="noindex"/> tag
remove_noindex() {
  file_path="$1"
  relative_path="${file_path#$HTML_DIR/}"

  # Use sed to remove noindex tag
  sed -i -E "s|<meta name=\"robots\" content=\"noindex\"/>||" "$file_path"
  echo "Removed noindex tag from: $file_path"
}

# Find all .html files and remove noindex tag
while read allowed_file; do
  find "$HTML_DIR" -type f -name "$allowed_file" | while read -r file; do
    remove_noindex "$file"
  done
done <$WHITE_LIST