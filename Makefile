PROJECT		= ft_ssl
FLAGS		= -Wall -Wextra -Werror -pedantic
CC			= clang
FT_MD5_SRC	= ft_md5/md5.c exec_manager.c main.c
INC			= include

all :
	@${CC} ${FT_MD5_SRC} -I ${INC} -o ${PROJECT}
	@echo "Compiled"