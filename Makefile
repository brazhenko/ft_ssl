PROJECT		= ft_ssl
FLAGS		= -Wall -Wextra -Werror -pedantic -g
CC			= clang
FT_MD5_SRC	= ft_md5/md5.c utilities/nstrjoin.c utilities/is_flag.c exec_manager.c main.c
INC			= include

all :
	@${CC} -O3 ${FT_MD5_SRC} -I ${INC} -o ${PROJECT}
	@echo "Compiled"
