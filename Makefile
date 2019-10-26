PROJECT		= ft_ssl
FLAGS		= -Wall -Wextra -Werror -pedantic -g
CC			= clang
BUILD_DIR   = build
FT_MD5_SRC	= 	\
				ssl/exec_manager.c \
				ssl/main.c \
				md5/md5.c \
				md5/print_md5.c \
				sha256/sha256.c \
				sha256/print_sha256.c \
				sha256/calc_sha256_from_string.c \
				sha256/calc_sha256_from_fd.c \
				utilities/nstrjoin.c \
				utilities/is_flag.c \
				utilities/debug.c \

INC			= include

all :
	@${CC} -O2 ${FT_MD5_SRC} -I ${INC} -o ${PROJECT}
	@echo "Compiled"

test256:
	shasum -a tests/abc
	./ssl sha256 tests/abc
	@echo "\n"
	shasum -a tests/64l
	./ssl sha256 tests/64l
	@echo "\n"
	shasum -a tests/a
	./ssl sha256 tests/a
	@echo "\n"
	shasum -a tests/a
	./ssl sha256 tests/a
