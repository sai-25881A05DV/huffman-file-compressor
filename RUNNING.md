# How to Run the Project

This project builds a command-line executable named `compressor`.

## Build

```bash
make
```

This compiles `main.cpp` and `huffmancodec.cpp` and creates the `compressor` binary.

## Show Help

```bash
./compressor --help
```

You can also use:

```bash
make run
```

## Compress a File

```bash
./compressor --compress <input_file> <output_file>
```

Example:

```bash
./compressor --compress document.txt document.huff
```

This creates the compressed file and also writes a matching tree file named `document.huff.tree`.

## Decompress a File

```bash
./compressor --decompress <input_file> <output_file>
```

Example:

```bash
./compressor --decompress document.huff document.txt
```

Important: decompression expects the tree file next to the compressed file. For `document.huff`, it looks for `document.huff.tree`.

## Run the Built-in Test

```bash
make test
```

This creates a sample text file, compresses it, decompresses it, and compares the result.

## Clean Build Files

```bash
make clean
```

This removes the executable and generated artifacts such as object files, `.huff`, `.tree`, and `.txt` files.

## If You Want This in README

Add a short section like this to `README.md`:

```md
## How to Run

- `make` to build the project
- `./compressor --help` to see usage
- `./compressor --compress <input_file> <output_file>` to compress a file
- `./compressor --decompress <input_file> <output_file>` to decompress a file
- `make test` to run the sample compression/decompression check
- `make clean` to remove generated files
```
