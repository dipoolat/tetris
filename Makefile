all: build run

build:
	@gcc -g figure.c main.c termius.c file_reader.c -lncurses -o tetris

run: build
	@./tetris

style:
	@clang-format -i *.c *.h