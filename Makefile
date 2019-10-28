PROJECT		= ft_ssl
FLAGS		= -Wall -Wextra -Werror -pedantic -g
CC			= clang
INC			= include
BUILD_DIR   = build

CC=gcc
CFLAGS=-c -Wall -I include
LDFLAGS=
SOURCES= 				ssl/command_executor.c \
         				ssl/main.c \
         				md5/md5.c \
         				md5/calculate_md5_from_string.c \
         				md5/calculate_md5_from_fd.c \
         				md5/calculate_md5_block.c \
         				md5/print_md5.c \
         				sha256/sha256.c \
         				sha256/print_sha256.c \
         				sha256/calc_sha256_from_string.c \
         				sha256/calc_sha256_from_fd.c \
         				utilities/nstrjoin.c \
         				utilities/is_flag.c \
         				utilities/debug.c \


clean:
	rm -rf */*.o

OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

test256:
	shasum -a tests/abc
	./ft_ssl sha256 tests/abc
	@echo "\n"
	shasum -a tests/64l
	./ft_ssl sha256 tests/64l
	@echo "\n"
	shasum -a tests/a
	./ft_ssl sha256 tests/a
	@echo "\n"
	shasum -a tests/a
	./ft_ssl sha256 tests/a
