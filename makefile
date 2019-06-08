### Flags

CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror

compile: src/*.c src/*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) src/*.c -o sudokusolver.out
	@./sudokusolver.out
