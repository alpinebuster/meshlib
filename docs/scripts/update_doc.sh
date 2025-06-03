#!/bin/bash

if [ $# -lt 1 ]; then
    echo "[INFO] Target directory is not specified. Used \"MeshLib/local\""
fi

# Use "MeshLib/local" as default if $1 is not provided
TARGET_DIR="${1:-MeshLib/local}"

#preparing files
bash ./scripts/pre.sh "$TARGET_DIR"
if [ $? -ne 0 ]; then
    echo "[ERROR] Problem in preparing files. Abort operation."
    exit 1
fi

#create output directory
mkdir -p ${TARGET_DIR}/html
#clear output directory
rm -rf ${TARGET_DIR}/html/*

MODULES=(Py Cpp Main)
#generate tag files
for MODULE in ${MODULES[*]}
do
    sed -e "s|GENERATE_TAGFILE\s*=.*|GENERATE_TAGFILE = MeshLib/MeshLib${MODULE}.tag|" -i Doxyfile${MODULE}
    doxygen ./Doxyfile${MODULE} 1 >> log_tag.txt
    sed -e "s|GENERATE_TAGFILE\s*=.*|GENERATE_TAGFILE =|" -i Doxyfile${MODULE}
done
rm -rf ${TARGET_DIR}/html/*

#final generation of documentation
sed -e "s|TAGFILES\s*=.*|TAGFILES = MeshLib/MeshLibPy.tag=./Py MeshLib/MeshLibCpp.tag=./Cpp|" -i DoxyfileMain
doxygen ./DoxyfileMain 1 >> log.txt
sed -e 's|<\!-- No Index Part -->|<meta name=\"robots\" content=\"noindex, nofollow\">|' -i html_header.html
sed -e "s|TAGFILES\s*=.*|TAGFILES = MeshLib/MeshLibMain.tag=../ MeshLib/MeshLibCpp.tag=../Cpp|" -i DoxyfilePy
doxygen ./DoxyfilePy 1 >> log.txt
sed -e "s|TAGFILES\s*=.*|TAGFILES = MeshLib/MeshLibMain.tag=../ MeshLib/MeshLibPy.tag=../Py|" -i DoxyfileCpp
doxygen ./DoxyfileCpp 1 >> log.txt

./scripts/restore_files.sh
./scripts/post.sh "$TARGET_DIR"
