# Meshlib Docs
This repository is test documentary holder for https://github.com/alpinebuster/meshlib

## Instruction

### Prepare
1. Install Doxygen 1.11 or later (via a package manager or after downloading from https://www.doxygen.nl/download.html)
2. Install sed (usually pre-installed on Unix(-like) systems, Windows version is available at https://gnuwin32.sourceforge.net/packages/sed.htm)
3. Download MeshLib and documentation rerepositories
```bash
cd workdir
git clone https://github.com/alpinebuster/meshlib.git
```

### Build documentation
1. Getting python stub-files (for python documentation update)
It's not critically important for generatio and can be skipped in test (local) generation
1.a From meshlib python package
1.b Manual geneartion
Use this manual https://github.com/MeshInspector/MeshLib/blob/master/scripts/mrbind/README.md
2. Build documentation
You can build release, dev, or local version of documentation. To do this, change *target_folder* to "MeshLib", "MeshLib/dev" or "MeshLib/local". Default target_folder is "MeshLib/local"
```bash
cd MeshInspector.github.io
./scripts/update_doc.sh target_folder
```
For manual generation see script ./scripts/update_doc.sh
3. Commit and push changes to this repository
**Note!** Dont recommend push changes in MeshLib/dev folder because this folder will be updated after commit in master branch or after build PR with tag update-doc in MeshLib repository
4. Check out the results at https://meshinspector.github.io/MeshLib/html/

### Local test
1. Run python http server
```bash
python3 -m http.server 8000
```
2. Open in browser http://127.0.0.1:8000/MeshLib/dev/html, http://127.0.0.1:8000/MeshLib/dev/html or http://127.0.0.1:8000/MeshLib/local/html (according target_folder)
**Note!** http://127.0.0.1:8000 will be redirected to https://meshlib.io/documentation
