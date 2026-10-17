# 打包说明

目标是便携目录：`LinNote` 可执行文件 + 依赖的 Qt 库（可用 `linuxdeployqt` / `cqtdeployer` 等收集）放在同一文件夹。

用户数据始终在该文件夹下的 `data/`，删除软件时整夹删掉即可。
