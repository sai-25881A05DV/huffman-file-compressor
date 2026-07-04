# Huffman File Compressor

This project provides a small command-line utility for compressing and decompressing text files with Huffman coding.

## Quick Start

Build the project with:

```bash
make
```

That creates the `compressor` executable in the project root.

If you want to see the available commands, run:

```bash
./compressor --help
```

## Usage

Compress a file:

```bash
./compressor --compress input.txt output.huff
```

Decompress it later:

```bash
./compressor --decompress output.huff restored.txt
```

When a file is compressed, the program also writes a matching tree file named after the compressed output, such as `output.huff.tree`. Keep that tree file with the compressed file, since decompression needs both.

## Helpful Commands

- `make run` shows the help screen.
- `make test` runs a full compress/decompress check with a sample file.
- `make clean` removes the executable and generated files.

## Install (optional)

If you want to make `compressor` available system-wide, install it to `/usr/local/bin` (or a different prefix):

```bash
# build
make

# install (may require sudo)
sudo make install

# uninstall
sudo make uninstall
```

You can also run the included `install.sh` which builds then installs (it will use `sudo` if required):

```bash
./install.sh
```

## Example Workflow

If you have `document.txt`, the typical flow looks like this:

```bash
make
./compressor --compress document.txt document.huff
./compressor --decompress document.huff document_restored.txt
```

If everything worked, `document_restored.txt` should match the original file.