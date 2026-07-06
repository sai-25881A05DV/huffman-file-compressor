<div align="center">

# 🌲 Huffman File Compressor

**A blazing-fast, dependency-free C++ CLI tool for lossless text compression using Huffman coding.**

[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-00599C?style=flat-square&logo=cplusplus)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/build-make-brightgreen?style=flat-square)](#quick-start)
[![License](https://img.shields.io/badge/license-MIT-blue?style=flat-square)](#license)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey?style=flat-square)](#install-optional)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-ff69b4?style=flat-square)](#contributing)

*Shrink your text files down to size — no Python, no bloated libraries, just clean C++ and classic computer science.*

</div>

---

## 📖 What is this?

**Huffman File Compressor** is a lightweight command-line utility that compresses and decompresses text files using **Huffman coding** — the same greedy, frequency-based algorithm that powers parts of ZIP, JPEG, and MP3 compression.

It was built to be simple enough for a first-year CS student to read end-to-end, yet complete enough to actually compress real files reliably.

```
Original file  ──►  Frequency Analysis  ──►  Huffman Tree  ──►  Bitstream  ──►  .huff (compressed)
.huff + .tree  ──►  Rebuild Tree         ──►  Decode Bits   ──►  Original file (restored)
```

---

## ✨ Features

- 🗜️ **Real compression** — encodes characters as variable-length bit sequences based on frequency
- 🔁 **Lossless round-trip** — decompressed output is byte-for-byte identical to the original
- ⚡ **Zero dependencies** — pure C++, builds with a single `make`
- 🧩 **Simple two-file format** — `.huff` (compressed data) + `.huff.tree` (the tree needed to decode)
- 🧪 **Built-in test suite** — `make test` runs a full compress → decompress → verify cycle
- 🛠️ **Installable** — drop it into `/usr/local/bin` and use it like any other system tool
- 📚 **Readable codebase** — great for learning how Huffman coding works in practice

---

## 🚀 Quick Start

```bash
# Clone the repo
git clone https://github.com/sai-25881A05DV/huffman-file-compressor.git
cd huffman-file-compressor

# Build
make
```

This produces a `compressor` executable in the project root.

```bash
./compressor --help
```

---

## 🧑‍💻 Usage

**Compress a file:**

```bash
./compressor --compress input.txt output.huff
```

**Decompress it back:**

```bash
./compressor --decompress output.huff restored.txt
```

> ⚠️ **Important:** Compressing a file also writes a matching tree file (e.g. `output.huff.tree`). Keep it alongside the compressed file — decompression needs both to rebuild the original data.

### Example Workflow

```bash
make
./compressor --compress document.txt document.huff
./compressor --decompress document.huff document_restored.txt

diff document.txt document_restored.txt   # should show no differences
```

---

## 🛠️ Helpful Commands

| Command        | What it does                                              |
|-----------------|------------------------------------------------------------|
| `make`          | Builds the `compressor` executable                         |
| `make run`      | Shows the help screen                                       |
| `make test`     | Runs a full compress/decompress cycle on a sample file      |
| `make clean`    | Removes the executable and generated files                  |

---

## 📦 Install (optional)

Make `compressor` available system-wide:

```bash
sudo make install      # installs to /usr/local/bin
sudo make uninstall    # removes it
```

Or use the bundled installer script, which builds then installs automatically:

```bash
./install.sh
```

---

## 🗂️ Project Structure

```
huffman-file-compressor/
├── main.cpp               # CLI entry point & argument parsing
├── huffmancodec.h          # Huffman codec class declarations
├── huffmancodec.cpp         # Core encoding/decoding logic
├── makefile                # Build automation
├── install.sh              # Build + install helper script
├── test_huffman.cpp         # Unit tests for the codec
├── test_full.cpp            # End-to-end compression test
├── test_decode.cpp          # Decode-path tests
├── test_complete_cycle.cpp  # Full compress/decompress cycle test
└── text_encode.cpp          # Text encoding helper
```

---

## 🧠 How Huffman Coding Works (in 30 seconds)

1. Count how often each character appears in the file.
2. Build a binary tree where frequent characters end up with **shorter** bit codes and rare characters get **longer** ones (a min-heap/priority-queue driven greedy algorithm).
3. Replace every character in the file with its bit code — frequent letters take less space, so the overall file shrinks.
4. Save the tree alongside the encoded bits so the decoder knows how to reverse the process exactly.

This is why the tool needs both the `.huff` file *and* its `.huff.tree` — the tree **is** the decompression key.

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!

1. Fork the repo
2. Create a branch: `git checkout -b feature/your-feature`
3. Commit your changes: `git commit -m "Add your feature"`
4. Push and open a Pull Request

Beginner-friendly issues and suggestions for extending this to other file types (binary, images) are especially welcome.

---

## 📄 License

This project is open source. Feel free to use, modify, and learn from it.

---

<div align="center">

**If this project helped you understand Huffman coding, consider giving it a ⭐!**

</div>
