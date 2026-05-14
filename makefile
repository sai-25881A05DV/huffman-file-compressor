# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -O2

# Target executable name
TARGET = compressor

# Object files needed
OBJS = huffmancodec.o main.o

# Default target (what happens when you type 'make')
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile huffmancodec.cpp to huffmancodec.o
huffmancodec.o: huffmancodec.cpp huffmancodec.h
	$(CXX) $(CXXFLAGS) -c huffmancodec.cpp -o huffmancodec.o

# Compile main.cpp to main.o
main.o: main.cpp huffmancodec.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET) *.huff *.tree *.txt

# Run the program with help
run: $(TARGET)
	./$(TARGET) --help

# Test the compressor
test: $(TARGET)
	@echo "Creating test file..."
	@echo "Hello Huffman World!" > test.txt
	@echo "Compressing..."
	@./$(TARGET) --compress test.txt test.huff
	@echo "Decompressing..."
	@./$(TARGET) --decompress test.huff test_decoded.txt
	@echo "Verifying..."
	@diff test.txt test_decoded.txt && echo "✅ SUCCESS!" || echo "❌ FAILED!"

# Help - show available commands
help:
	@echo "Available commands:"
	@echo "  make          - Build the program"
	@echo "  make clean    - Remove compiled files"
	@echo "  make run      - Run the program with --help"
	@echo "  make test     - Test compress/decompress cycle"
	@echo "  make help     - Show this help"

# Phony targets (not actual files)
.PHONY: all clean run test help