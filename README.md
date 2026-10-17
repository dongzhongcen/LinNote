<div align="center">

# LinNote

**便携式 Linux 学习笔记桌面工具**

*本地笔记本 · 常用指令速查 · 常用配置下载*

[English](README.en.md)

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)](#)
[![Qt](https://img.shields.io/badge/Qt-6-green.svg)](#)

</div>

## 简介

LinNote 是一个 **Qt 便携桌面应用**，以**笔记本**为核心，附带常用 Linux 指令查询与常用配置文件下载。

- **便携**：程序与数据同目录（或程序旁的 `data/`），拷到 U 盘即可用
- **无残留**：不写入 `~/.config`、不写系统目录；删除整个程序目录即完全卸载
- **离线友好**：指令与笔记本地保存；配置下载仅在你主动触发时联网

## 第一版范围

| 模块 | 说明 |
|------|------|
| 笔记本 | 新建 / 编辑 / 搜索笔记（本地存储） |
| 指令查询 | 内置常用 Linux 命令说明与示例 |
| 配置下载 | 下载常用配置模板到本地（可选） |

## 状态

仓库已创建，应用实现进行中。构建与发布方式将随后补齐。

## 开发

计划使用 Qt 6（Widgets 或 Quick）。具体工程结构由开发提交后更新本节。

```bash
git clone https://github.com/dongzhongcen/LinNote.git
cd LinNote
```

## 许可证

[MIT](LICENSE)
