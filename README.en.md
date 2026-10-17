<div align="center">

# LinNote

**A portable notebook, with Linux command lookup and common config downloads**

*Qt portable desktop app · data next to the binary · clean deletes*

[简体中文](README.md) | **English**

[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)
[![Qt](https://img.shields.io/badge/Qt-6-green)](https://www.qt.io/)
[![Platform](https://img.shields.io/badge/platform-Linux-orange)](https://github.com/dongzhongcen/LinNote)

</div>

## Overview

LinNote is a **portable** Qt utility. **v0.1 focuses on the notebook**; command lookup and config downloads are secondary:

1. **Notebook** (primary) — plain-text notes, one file per note
2. **Command lookup** — offline catalog of common Linux commands
3. **Config downloads** — fetch useful config templates into the app folder

All user data lives under `data/` next to the executable (not under `~/.config`). Deleting a note or download removes the file itself. Uninstall by deleting the app folder—no leftovers.

## Build

Requires Qt 6 (Widgets, Network), CMake ≥ 3.16, and a C++17 compiler.

```bash
git clone https://github.com/dongzhongcen/LinNote.git
cd LinNote
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/LinNote
```

## License

[MIT](LICENSE)
