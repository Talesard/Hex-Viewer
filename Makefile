CC=g++
CFLAGS=-o2
SOURCE_DIR=src
EXECUTABLE=hex.exe
SOURCES=*.cpp

build:
	$(CC) $(CFLAGS) $(SOURCE_DIR)\\$(SOURCES) -o $(EXECUTABLE)
test:
	@echo off && cd tests && python -m unittest -v test.py && cd ..
clean:
	@echo off && del $(EXECUTABLE)
help:
	@echo off && echo Available args: build, test, clean
