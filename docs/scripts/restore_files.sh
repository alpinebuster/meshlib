#!/bin/bash

# Remove temporary files
rm html_header.html html_footer.html html_stylesheet.css

MODULES=(Py Cpp Main)
for MODULE in ${MODULES[*]}
do
    # Restore Doxyfile 
    [[ -f Doxyfile${MODULE}.bak ]] && mv Doxyfile${MODULE}.bak Doxyfile${MODULE}
    # Restore tag file 
    rm -f MeshLib/MeshLib${MODULE}.tag 
done