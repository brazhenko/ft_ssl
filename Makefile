PROJECT		= ft_ssl
FLAGS		= -Wall -Wextra -Werror -pedantic -g
CC			= clang
INC			= include
BUILD_DIR   = build

CC=gcc
CFLAGS=-c -Wall -I include
LDFLAGS=
SOURCES=				ssl/main.c \
						ssl/command_executor.c \
						ssl/parse_hash_flags.c \
						ssl/hash_executor.c \
         				ssl/help.c \
         				md5/md5.c \
         				md5/calculate_md5_from_string.c \
         				md5/calculate_md5_from_fd.c \
         				md5/calculate_md5_block.c \
         				md5/calculate_md5_buf_padding.c \
         				md5/print_md5.c \
         				sha256/sha256.c \
         				sha256/print_sha256.c \
         				sha256/calc_sha256_from_string.c \
         				sha256/calc_sha256_buf_padding.c \
         				sha256/calc_sha256_from_fd.c \
         				utilities/nstrjoin.c \
         				utilities/is_flag.c \
         				#utilities/debug.c \


OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(PROJECT)


$(PROJECT): $(OBJECTS)
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@echo "Compiled!"

.c.o:
	@$(CC) $(CFLAGS) $< -o $@

allcl: all clean

clean:
	@rm -rf */*.o
	@echo "Object files removed"

fclean: clean
	@rm ${PROJECT}
	@echo ${PROJECT} removed

re: fclean all
