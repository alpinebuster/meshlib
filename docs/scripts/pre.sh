#!/bin/bash
set -eo pipefail

if [ $# -lt 1 ]; then
    echo "[INFO] Target directory is not specified. Used \"MeshLib/local\""
fi

# Use "MeshLib" as default if $1 is not provided
TARGET_DIR="${1:-MeshLib/local}"

# generate customizable HTML parts
doxygen -w html html_header.html html_footer.html html_stylesheet.css DoxyfileMain

# inject Google Analytics code into the HTML header
sed \
    -e "/<head>/r scripts/analytics/html_head.html" \
    -e "/<body>/r scripts/analytics/html_body.html" \
    -i html_header.html

# Additional insertion for html_head_canonical.html if $TARGET_DIR is "MeshLib"
if [ "$TARGET_DIR" == "MeshLib" ]; then
    sed \
        -e "/<head>/r scripts/analytics/html_head_canonical.html" \
        -i html_header.html
fi

# add doxygen-awesome scripts
sed -e "/<\/head>/q" html_header.html > html_header.html.tmp
sed -e "/<\/head>/d" -i html_header.html.tmp
cat scripts/doxygen-awesome-scripts.html >> html_header.html.tmp
sed -n -e "/<\/head>/,$ p" html_header.html >> html_header.html.tmp
rm html_header.html
mv html_header.html.tmp html_header.html
# set nofollow tag in footer
sed -i "s|href=|rel=\"nofollow\" href=|g" html_footer.html
# fix doxygen link in footer
sed -i "s|doxygen.org|doxygen.nl|g" html_footer.html

if [ ! -f ../MeshLib/scripts/doxygen/generate_doxygen_layout.sh ]; then
    echo "[ERROR] Can not found script to generate doxygen layout files"
    exit 1
fi

MODULES=(Py Cpp Main)
for MODULE in ${MODULES[*]}
do
    ../MeshLib/scripts/doxygen/generate_doxygen_layout.sh $MODULE
    # force Doxygen to use the custom HTML header
    sed -e "s|HTML_HEADER\s*=.*|HTML_HEADER = html_header.html|" -i.bak Doxyfile${MODULE}
    # force Doxygen to use the custom HTML footer
    sed -e "s|HTML_FOOTER\s*=.*|HTML_FOOTER = html_footer.html|" -i.bak Doxyfile${MODULE}
    # force Doxygen to use the custom output directory
    sed -e "s|OUTPUT_DIRECTORY\s*=.*|OUTPUT_DIRECTORY = ${TARGET_DIR}|" -i Doxyfile${MODULE}
done
