PROJECT		= ssl
FLAGS		= -Wall -Wextra -Werror -pedantic -g
CC			= clang
BUILD_DIR   = build
FT_MD5_SRC	= 	\
				ft_ssl/exec_manager.c ft_ssl/main.c \
				ft_md5/md5.c \
				ft_md5/print_md5.c \
				ft_sha256/ft_sha256.c \
				ft_sha256/print_sha256.c \
				ft_sha256/calc_sha256_from_string.c \
				ft_sha256/calc_sha256_from_fd.c \
				utilities/nstrjoin.c \
				utilities/is_flag.c \
				utilities/debug.c \

INC			= include

all :
	@${CC} -O2 ${FT_MD5_SRC} -I ${INC} -o ${PROJECT}
	@echo "Compiled"
