all: run build
build:
    gcc make.c -o make.exe
run:
    make.exe text.txt all