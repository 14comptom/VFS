# VFS

A Virtual File System (VFS) written in C.

## Description

VFS is a simple imlementation of a unix based file system.
It only supports basic files.
In this case, / is the origin of the file tree and does not represent users.

> **Project Status:** Early development (`v0.1.0`)

## Features

- Modular project structure
- Cross-platform Makefile
- Virtual disk creation
- Storage initialization
- Utility library

## Project Structure

```
VFS/
├── include/
├── src/
│   ├── fs/
│   ├── lib/
│   ├── shell/
│   └── storage/
├── Makefile
└── ...
```

## Building

```bash
make
```

## Running

```bash
make run
```

## Cleaning

```bash
make clean
```

## Requirements

- GCC
- Make
- C99-compatible compiler

## Version

Current version: **v0.1.0**

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.