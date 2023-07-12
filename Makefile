CC = gcc
OUT = fnc

all: build

clean:
	@rm -rfv build/${OUT}

build: clean src/main.c
	@${CC} -g -Wall src/main.c src/fn.c -o build/${OUT}
	@echo "\033[1;32mBuild Done!\033[0m"
