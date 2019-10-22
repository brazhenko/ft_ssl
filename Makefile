PROJECT		= ssl
FLAGS		= -Wall -Wextra -Werror -pedantic -g
CC			= clang
FT_MD5_SRC	= ft_md5/md5.c \
				utilities/nstrjoin.c \
				utilities/is_flag.c \
				ft_ssl/exec_manager.c ft_ssl/main.c \

INC			= include

all :
	@${CC} -O2 ${FT_MD5_SRC} -I ${INC} -o ${PROJECT}
	@echo "Compiled"
