# **************************************************************************** #
# GENERIC_VARIABLES

OBJ_DIR = build

# **************************************************************************** #
# COMPILER_OPTIONS

C_COMPILER = clang
C_STANDART = -std=c99
C_CFLAGS =  $(CFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror
C_LFLAGS =  $(CFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror

# **************************************************************************** #
# FT_SSL TARGET DESCRIPTION

FT_SSL_NAME = ft_ssl
FT_SSL_PATH = ssl
FT_SSL_FILE = ./ft_ssl
FT_SSL_SRCS = command_executor.c hash_executor.c help.c main.c parse_hash_flags.c encode_executor.c wrong_command_exit.c
FT_SSL_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(FT_SSL_SRCS))
FT_SSL_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(FT_SSL_SRCS))
FT_SSL_LIBS = -l ssl_utils -L . -l cipher -L . -l cipher_ctx -L . -l cipher_des -L . -l cipher_pbkdf -L . -l encode -L . -l base64 -L . -l encode_ctx -L . -l md5 -L . -l sha256 -L . -l rsautl -L . -l rsautl_ctx -L . -l key_io -L . -l genrsa -L . -l genrsa_ctx -L . -l rsa -L . -l rsa_ctx -L . -l rsa_breaker -L .
FT_SSL_INCS = -I include

# **************************************************************************** #
# SSL_UTILS TARGET DESCRIPTION

SSL_UTILS_NAME = ssl_utils
SSL_UTILS_PATH = ssl/utilities
SSL_UTILS_FILE = ./libssl_utils.a
SSL_UTILS_SRCS = nstrjoin.c print_uint32_bits.c fatal.c is_flag.c xmalloc.c print_uint64_bits.c smax.c mod_inverse.c int128convs.c solovay_strassen_test.c mem_xor.c print_hex_memory.c
SSL_UTILS_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(SSL_UTILS_SRCS))
SSL_UTILS_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(SSL_UTILS_SRCS))
SSL_UTILS_LIBS = 
SSL_UTILS_INCS = -I include

# **************************************************************************** #
# CIPHER TARGET DESCRIPTION

CIPHER_NAME = cipher
CIPHER_PATH = ssl
CIPHER_FILE = ./libcipher.a
CIPHER_SRCS = cipher_executor.c
CIPHER_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(CIPHER_SRCS))
CIPHER_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(CIPHER_SRCS))
CIPHER_LIBS = 
CIPHER_INCS = -I include

# **************************************************************************** #
# CIPHER_CTX TARGET DESCRIPTION

CIPHER_CTX_NAME = cipher_ctx
CIPHER_CTX_PATH = cipher/context
CIPHER_CTX_FILE = ./libcipher_ctx.a
CIPHER_CTX_SRCS = cphr_is_a_flag.c cphr_is_decrypt_mode.c cphr_is_encrypt_mode.c cphr_is_iv_set.c cphr_is_key_set.c cphr_is_pass_set.c cphr_is_salt_set.c cphr_argv_state_a.c cphr_argv_state_d.c cphr_argv_state_e.c cphr_argv_state_i.c cphr_argv_state_k.c cphr_argv_state_o.c cphr_argv_state_p.c cphr_argv_state_s.c cphr_argv_state_v.c set_cipher_init_vector.c set_cipher_password_from_stdin.c set_cipher_random_pass_salt.c set_cipher_pass_salt.c destruct_cipher_context.c set_cipher_key.c set_cipher_bufsize.c des_argv_states.c init_cipher_context.c set_cipher_input_file.c set_cipher_output_file.c
CIPHER_CTX_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(CIPHER_CTX_SRCS))
CIPHER_CTX_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(CIPHER_CTX_SRCS))
CIPHER_CTX_LIBS = 
CIPHER_CTX_INCS = -I include

# **************************************************************************** #
# CIPHER_DES TARGET DESCRIPTION

CIPHER_DES_NAME = cipher_des
CIPHER_DES_PATH = cipher/des
CIPHER_DES_FILE = ./libcipher_des.a
CIPHER_DES_SRCS = des_ecb.c des_cbc.c des_cbc_encrypt.c des_cbc_decrypt.c des_ecb_encrypt.c des_ecb_decrypt.c des_get_block.c des_key_gen.c des_encode_block.c des_permutation.c des_swap_block_halves.c try_get_des_salt_from_fd.c s_permutation.c des.c des_cut_padding.c
CIPHER_DES_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(CIPHER_DES_SRCS))
CIPHER_DES_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(CIPHER_DES_SRCS))
CIPHER_DES_LIBS = 
CIPHER_DES_INCS = -I include

# **************************************************************************** #
# CIPHER_PBKDF TARGET DESCRIPTION

CIPHER_PBKDF_NAME = cipher_pbkdf
CIPHER_PBKDF_PATH = cipher/pbkdf
CIPHER_PBKDF_FILE = ./libcipher_pbkdf.a
CIPHER_PBKDF_SRCS = pbkdf_md5.c
CIPHER_PBKDF_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(CIPHER_PBKDF_SRCS))
CIPHER_PBKDF_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(CIPHER_PBKDF_SRCS))
CIPHER_PBKDF_LIBS = 
CIPHER_PBKDF_INCS = -I include

# **************************************************************************** #
# ENCODE TARGET DESCRIPTION

ENCODE_NAME = encode
ENCODE_PATH = encode
ENCODE_FILE = ./libencode.a
ENCODE_SRCS = encode_usage.c
ENCODE_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(ENCODE_SRCS))
ENCODE_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(ENCODE_SRCS))
ENCODE_LIBS = 
ENCODE_INCS = -I include

# **************************************************************************** #
# BASE64 TARGET DESCRIPTION

BASE64_NAME = base64
BASE64_PATH = encode/base64
BASE64_FILE = ./libbase64.a
BASE64_SRCS = base64.c base64_decode.c base64_encode.c
BASE64_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(BASE64_SRCS))
BASE64_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(BASE64_SRCS))
BASE64_LIBS = 
BASE64_INCS = -I include

# **************************************************************************** #
# ENCODE_CTX TARGET DESCRIPTION

ENCODE_CTX_NAME = encode_ctx
ENCODE_CTX_PATH = encode/context
ENCODE_CTX_FILE = ./libencode_ctx.a
ENCODE_CTX_SRCS = init_encode_context.c set_decode_mode.c set_encode_mode.c set_input_file.c set_output_file.c parse_encode_argv.c encode_argv_states.c argv_errors.c destruct_encode_context.c
ENCODE_CTX_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(ENCODE_CTX_SRCS))
ENCODE_CTX_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(ENCODE_CTX_SRCS))
ENCODE_CTX_LIBS = 
ENCODE_CTX_INCS = -I include

# **************************************************************************** #
# MD5 TARGET DESCRIPTION

MD5_NAME = md5
MD5_PATH = hash/md5
MD5_FILE = ./libmd5.a
MD5_SRCS = calculate_md5_block.c calculate_md5_buf_padding.c calculate_md5_from_fd.c calculate_md5_from_string.c md5.c print_md5.c calculate_md5_from_mem.c
MD5_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(MD5_SRCS))
MD5_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(MD5_SRCS))
MD5_LIBS = 
MD5_INCS = -I include

# **************************************************************************** #
# SHA256 TARGET DESCRIPTION

SHA256_NAME = sha256
SHA256_PATH = hash/sha256
SHA256_FILE = ./libsha256.a
SHA256_SRCS = calc_sha256_buf_padding.c calc_sha256_from_fd.c calc_sha256_from_string.c print_sha256.c sha256.c
SHA256_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(SHA256_SRCS))
SHA256_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(SHA256_SRCS))
SHA256_LIBS = 
SHA256_INCS = -I include

# **************************************************************************** #
# RSAUTL TARGET DESCRIPTION

RSAUTL_NAME = rsautl
RSAUTL_PATH = rsa/rsautl
RSAUTL_FILE = ./librsautl.a
RSAUTL_SRCS = rsa_utl_routines.c rsautl.c
RSAUTL_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(RSAUTL_SRCS))
RSAUTL_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(RSAUTL_SRCS))
RSAUTL_LIBS = 
RSAUTL_INCS = -I include

# **************************************************************************** #
# RSAUTL_CTX TARGET DESCRIPTION

RSAUTL_CTX_NAME = rsautl_ctx
RSAUTL_CTX_PATH = rsa/rsautl_ctx
RSAUTL_CTX_FILE = ./librsautl_ctx.a
RSAUTL_CTX_SRCS = parse_rsautl2.c parse_rsautl_args.c
RSAUTL_CTX_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(RSAUTL_CTX_SRCS))
RSAUTL_CTX_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(RSAUTL_CTX_SRCS))
RSAUTL_CTX_LIBS = 
RSAUTL_CTX_INCS = -I include

# **************************************************************************** #
# KEY_IO TARGET DESCRIPTION

KEY_IO_NAME = key_io
KEY_IO_PATH = rsa/key_io
KEY_IO_FILE = ./libkey_io.a
KEY_IO_SRCS = input_routines.c output_routines.c routines1.c routines2.c
KEY_IO_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(KEY_IO_SRCS))
KEY_IO_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(KEY_IO_SRCS))
KEY_IO_LIBS = 
KEY_IO_INCS = -I include

# **************************************************************************** #
# GENRSA TARGET DESCRIPTION

GENRSA_NAME = genrsa
GENRSA_PATH = rsa/genrsa
GENRSA_FILE = ./libgenrsa.a
GENRSA_SRCS = genrsa.c
GENRSA_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(GENRSA_SRCS))
GENRSA_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(GENRSA_SRCS))
GENRSA_LIBS = 
GENRSA_INCS = -I include

# **************************************************************************** #
# GENRSA_CTX TARGET DESCRIPTION

GENRSA_CTX_NAME = genrsa_ctx
GENRSA_CTX_PATH = rsa/genrsa_ctx
GENRSA_CTX_FILE = ./libgenrsa_ctx.a
GENRSA_CTX_SRCS = genrsa_ctx2.c parse_gen_rsa_args.c
GENRSA_CTX_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(GENRSA_CTX_SRCS))
GENRSA_CTX_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(GENRSA_CTX_SRCS))
GENRSA_CTX_LIBS = 
GENRSA_CTX_INCS = -I include

# **************************************************************************** #
# RSA TARGET DESCRIPTION

RSA_NAME = rsa
RSA_PATH = rsa/rsa
RSA_FILE = ./librsa.a
RSA_SRCS = rsa.c rsa2.c
RSA_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(RSA_SRCS))
RSA_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(RSA_SRCS))
RSA_LIBS = 
RSA_INCS = -I include

# **************************************************************************** #
# RSA_CTX TARGET DESCRIPTION

RSA_CTX_NAME = rsa_ctx
RSA_CTX_PATH = rsa/rsa_ctx
RSA_CTX_FILE = ./librsa_ctx.a
RSA_CTX_SRCS = parse_rsa_args.c rsa_ctx2.c
RSA_CTX_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(RSA_CTX_SRCS))
RSA_CTX_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(RSA_CTX_SRCS))
RSA_CTX_LIBS = 
RSA_CTX_INCS = -I include

# **************************************************************************** #
# RSA_BREAKER TARGET DESCRIPTION

RSA_BREAKER_NAME = rsa_breaker
RSA_BREAKER_PATH = rsa/rsa_breaker
RSA_BREAKER_FILE = ./librsa_breaker.a
RSA_BREAKER_SRCS = rsa_breaker.c
RSA_BREAKER_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(RSA_BREAKER_SRCS))
RSA_BREAKER_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(RSA_BREAKER_SRCS))
RSA_BREAKER_LIBS = 
RSA_BREAKER_INCS = -I include

# **************************************************************************** #
# GENERIC RULES

.PHONY: all re clean fclean
.DEFAULT_GOAL = all

all: $(SSL_UTILS_FILE) $(CIPHER_FILE) $(CIPHER_CTX_FILE) $(CIPHER_DES_FILE) $(CIPHER_PBKDF_FILE) $(ENCODE_FILE) $(BASE64_FILE) $(ENCODE_CTX_FILE) $(MD5_FILE) $(SHA256_FILE) $(RSAUTL_FILE) $(RSAUTL_CTX_FILE) $(KEY_IO_FILE) $(GENRSA_FILE) $(GENRSA_CTX_FILE) $(RSA_FILE) $(RSA_CTX_FILE) $(RSA_BREAKER_FILE) $(FT_SSL_FILE)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(SSL_UTILS_FILE) $(CIPHER_FILE) $(CIPHER_CTX_FILE) $(CIPHER_DES_FILE) $(CIPHER_PBKDF_FILE) $(ENCODE_FILE) $(BASE64_FILE) $(ENCODE_CTX_FILE) $(MD5_FILE) $(SHA256_FILE) $(RSAUTL_FILE) $(RSAUTL_CTX_FILE) $(KEY_IO_FILE) $(GENRSA_FILE) $(GENRSA_CTX_FILE) $(RSA_FILE) $(RSA_CTX_FILE) $(RSA_BREAKER_FILE) $(FT_SSL_FILE)

re: fclean all

$(FT_SSL_FILE): $(SSL_UTILS_FILE) $(CIPHER_FILE) $(CIPHER_CTX_FILE) $(CIPHER_DES_FILE) $(CIPHER_PBKDF_FILE) $(ENCODE_FILE) $(BASE64_FILE) $(ENCODE_CTX_FILE) $(MD5_FILE) $(SHA256_FILE) $(RSAUTL_FILE) $(RSAUTL_CTX_FILE) $(KEY_IO_FILE) $(GENRSA_FILE) $(GENRSA_CTX_FILE) $(RSA_FILE) $(RSA_CTX_FILE) $(RSA_BREAKER_FILE) $(FT_SSL_OBJS)
	@$(C_COMPILER) $(C_LFLAGS) $(C_STANDART) -o $(FT_SSL_FILE) $(FT_SSL_OBJS)  $(FT_SSL_LIBS)
	@printf 'Finished	\033[1;32m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(FT_SSL_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(FT_SSL_INCS) -o $@ -c $< -MMD

$(SSL_UTILS_FILE): $(SSL_UTILS_OBJS)
	@ar rc $(SSL_UTILS_FILE) $(SSL_UTILS_OBJS)
	@ranlib $(SSL_UTILS_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(SSL_UTILS_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(SSL_UTILS_INCS) -o $@ -c $< -MMD

$(CIPHER_FILE): $(CIPHER_OBJS)
	@ar rc $(CIPHER_FILE) $(CIPHER_OBJS)
	@ranlib $(CIPHER_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(CIPHER_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(CIPHER_INCS) -o $@ -c $< -MMD

$(CIPHER_CTX_FILE): $(CIPHER_CTX_OBJS)
	@ar rc $(CIPHER_CTX_FILE) $(CIPHER_CTX_OBJS)
	@ranlib $(CIPHER_CTX_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(CIPHER_CTX_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(CIPHER_CTX_INCS) -o $@ -c $< -MMD

$(CIPHER_DES_FILE): $(CIPHER_DES_OBJS)
	@ar rc $(CIPHER_DES_FILE) $(CIPHER_DES_OBJS)
	@ranlib $(CIPHER_DES_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(CIPHER_DES_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(CIPHER_DES_INCS) -o $@ -c $< -MMD

$(CIPHER_PBKDF_FILE): $(CIPHER_PBKDF_OBJS)
	@ar rc $(CIPHER_PBKDF_FILE) $(CIPHER_PBKDF_OBJS)
	@ranlib $(CIPHER_PBKDF_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(CIPHER_PBKDF_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(CIPHER_PBKDF_INCS) -o $@ -c $< -MMD

$(ENCODE_FILE): $(ENCODE_OBJS)
	@ar rc $(ENCODE_FILE) $(ENCODE_OBJS)
	@ranlib $(ENCODE_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(ENCODE_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(ENCODE_INCS) -o $@ -c $< -MMD

$(BASE64_FILE): $(BASE64_OBJS)
	@ar rc $(BASE64_FILE) $(BASE64_OBJS)
	@ranlib $(BASE64_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(BASE64_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(BASE64_INCS) -o $@ -c $< -MMD

$(ENCODE_CTX_FILE): $(ENCODE_CTX_OBJS)
	@ar rc $(ENCODE_CTX_FILE) $(ENCODE_CTX_OBJS)
	@ranlib $(ENCODE_CTX_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(ENCODE_CTX_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(ENCODE_CTX_INCS) -o $@ -c $< -MMD

$(MD5_FILE): $(MD5_OBJS)
	@ar rc $(MD5_FILE) $(MD5_OBJS)
	@ranlib $(MD5_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(MD5_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(MD5_INCS) -o $@ -c $< -MMD

$(SHA256_FILE): $(SHA256_OBJS)
	@ar rc $(SHA256_FILE) $(SHA256_OBJS)
	@ranlib $(SHA256_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(SHA256_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(SHA256_INCS) -o $@ -c $< -MMD

$(RSAUTL_FILE): $(RSAUTL_OBJS)
	@ar rc $(RSAUTL_FILE) $(RSAUTL_OBJS)
	@ranlib $(RSAUTL_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(RSAUTL_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(RSAUTL_INCS) -o $@ -c $< -MMD

$(RSAUTL_CTX_FILE): $(RSAUTL_CTX_OBJS)
	@ar rc $(RSAUTL_CTX_FILE) $(RSAUTL_CTX_OBJS)
	@ranlib $(RSAUTL_CTX_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(RSAUTL_CTX_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(RSAUTL_CTX_INCS) -o $@ -c $< -MMD

$(KEY_IO_FILE): $(KEY_IO_OBJS)
	@ar rc $(KEY_IO_FILE) $(KEY_IO_OBJS)
	@ranlib $(KEY_IO_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(KEY_IO_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(KEY_IO_INCS) -o $@ -c $< -MMD

$(GENRSA_FILE): $(GENRSA_OBJS)
	@ar rc $(GENRSA_FILE) $(GENRSA_OBJS)
	@ranlib $(GENRSA_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(GENRSA_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(GENRSA_INCS) -o $@ -c $< -MMD

$(GENRSA_CTX_FILE): $(GENRSA_CTX_OBJS)
	@ar rc $(GENRSA_CTX_FILE) $(GENRSA_CTX_OBJS)
	@ranlib $(GENRSA_CTX_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(GENRSA_CTX_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(GENRSA_CTX_INCS) -o $@ -c $< -MMD

$(RSA_FILE): $(RSA_OBJS)
	@ar rc $(RSA_FILE) $(RSA_OBJS)
	@ranlib $(RSA_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(RSA_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(RSA_INCS) -o $@ -c $< -MMD

$(RSA_CTX_FILE): $(RSA_CTX_OBJS)
	@ar rc $(RSA_CTX_FILE) $(RSA_CTX_OBJS)
	@ranlib $(RSA_CTX_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(RSA_CTX_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(RSA_CTX_INCS) -o $@ -c $< -MMD

$(RSA_BREAKER_FILE): $(RSA_BREAKER_OBJS)
	@ar rc $(RSA_BREAKER_FILE) $(RSA_BREAKER_OBJS)
	@ranlib $(RSA_BREAKER_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(RSA_BREAKER_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(RSA_BREAKER_INCS) -o $@ -c $< -MMD

-include $(FT_SSL_DEPS) $(SSL_UTILS_DEPS) $(CIPHER_DEPS) $(CIPHER_CTX_DEPS) $(CIPHER_DES_DEPS) $(CIPHER_PBKDF_DEPS) $(ENCODE_DEPS) $(BASE64_DEPS) $(ENCODE_CTX_DEPS) $(MD5_DEPS) $(SHA256_DEPS) $(RSAUTL_DEPS) $(RSAUTL_CTX_DEPS) $(KEY_IO_DEPS) $(GENRSA_DEPS) $(GENRSA_CTX_DEPS) $(RSA_DEPS) $(RSA_CTX_DEPS) $(RSA_BREAKER_DEPS)
