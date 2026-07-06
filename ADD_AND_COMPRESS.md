# Add a File and Compress It

This guide shows how to:
1. Add (create) a text file
2. Compress it using the `compressor` program

## 1) Build the project

From the project root, run:

```bash
make
```

## 2) Add a file

Create a sample text file:

```bash
echo "This is my file to compress." > myfile.txt
```

You can also edit `myfile.txt` manually in VS Code and save it.

## 3) Compress the file

Run:

```bash
./compressor --compress myfile.txt myfile.huff
```

After compression, you should see:
- `myfile.huff`
- `myfile.huff.tree`

Keep both files. The `.tree` file is required for decompression.

## 4) (Optional) Decompress to verify

```bash
./compressor --decompress myfile.huff myfile_restored.txt
```

Compare original and restored files:

```bash
diff myfile.txt myfile_restored.txt && echo "Files match"
```
