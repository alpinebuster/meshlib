#!/bin/sed -f
# remove BOM
/^\xEF\xBB\xBF/ d
# comment out code lines
\:^///:! s:^:/// :
