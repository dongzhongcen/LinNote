<div align="center">

# LinNote

**便携笔记本，附带 Linux 指令查询与常用配置下载**

*Qt 便携桌面工具 · 数据在程序旁 · 删除不留残留*

**简体中文** | [English](README.en.md)

[![许可证](https://img.shields.io/badge/许可证-MIT-blue)](LICENSE)
[![Qt](https://img.shields.io/badge/Qt-6-green)](https://www.qt.io/)
[![平台](https://img.shields.io/badge/平台-Linux-orange)](https://github.com/dongzhongcen/LinNote)

</div>

## 简介

LinNote 是一个 **便携（portable）** 的 Qt 小工具。**第一版以笔记本为主**，指令查询和配置下载是附带能力：

1. **笔记本**（主功能）— 本地纯文本笔记，一条笔记一个文件
2. **指令查询** — 内置常见 Linux 命令速查（可离线）
3. **配置下载** — 拉取常用配置模板到程序旁目录

用户数据只写在可执行文件旁边的 `data/`，**不写** `~/.config` 等系统目录。删除笔记或已下载配置时，会直接删除对应文件；卸载时删掉整个程序目录即可，无残留。

## 功能

- 默认打开「笔记本」页签；另有指令查询、配置下载
- 笔记保存在 `data/notes/<id>.txt`；删除即移除该文件
- 配置下载到 `data/downloads/`；删除会清除本地副本
- 命令目录来自内置 JSON，可按名称、简介、标签过滤
- MIT 许可，可用 CMake + Qt6 自行编译

## 构建

依赖：Qt 6（Widgets、Network）、CMake ≥ 3.16、C++17 编译器。

```bash
git clone https://github.com/dongzhongcen/LinNote.git
cd LinNote
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/LinNote
```

便携使用：把编译出的 `LinNote` 与所需 Qt 库放在同一文件夹；首次运行会自动创建 `data/notes` 与 `data/downloads`。

## 删除与残留

| 操作 | 行为 |
| --- | --- |
| 删除笔记 | 删除 `data/notes/<id>.txt` |
| 删除已下载配置 | 删除 `data/downloads/<文件名>` |
| 卸载软件 | 删除程序目录（含 `data/`）即可 |

## 许可证

[MIT](LICENSE)
