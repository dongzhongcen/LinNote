# 打包说明

目标是便携目录：`LinNote` 可执行文件 + 依赖的 Qt 库（可用 `linuxdeployqt` / `cqtdeployer` 等收集）放在同一文件夹。

**即使用系统路径安装（例如 `cmake --install` 到 `/usr`），运行时笔记与下载仍写在可执行文件旁边的 `data/`**，不写 `~/.config`。删除软件时以「删掉程序所在目录（含 `data/`）」为准，才无残留。
