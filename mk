PROJECT		= ft_ssl
FLAGS		= -Wall -Wextra -Werror -pedantic -g
CC			= clang
INC			= include
BUILD_DIR   = build

CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -I include
LDFLAGS=
SOURCES=				ssl/main.c \
						ssl/command_executor.c \
						ssl/parse_hash_flags.c \
						ssl/hash_executor.c \
         				ssl/help.c \
						ssl/cipher_executor.c \
						ssl/encode_executor.c \
						ssl/wrong_command_exit.c \
						\
         				hash/md5/md5.c \
         				hash/md5/calculate_md5_from_string.c \
         				hash/md5/calculate_md5_from_fd.c \
         				hash/md5/calculate_md5_block.c \
         				hash/md5/calculate_md5_buf_padding.c \
         				hash/md5/print_md5.c \
         				hash/md5/calculate_md5_from_mem.c \
						\
         				hash/sha256/sha256.c \
         				hash/sha256/print_sha256.c \
         				hash/sha256/calc_sha256_from_string.c \
         				hash/sha256/calc_sha256_buf_padding.c \
         				hash/sha256/calc_sha256_from_fd.c \
						\
         				ssl/utilities/nstrjoin.c \
         				ssl/utilities/is_flag.c \
						ssl/utilities/mem_xor.c \
						ssl/utilities/print_hex_memory.c \
						ssl/utilities/print_uint32_bits.c \
						ssl/utilities/print_uint64_bits.c \
						ssl/utilities/xmalloc.c \
						\
						encode/encode_usage.c \
						\
						encode/base64/base64_encode.c \
						encode/base64/base64_decode.c \
						encode/base64/base64.c \
						\
						encode/context/argv_errors.c \
						encode/context/destruct_encode_context.c \
						encode/context/encode_argv_states.c \
						encode/context/init_encode_context.c \
						encode/context/parse_encode_argv.c \
						encode/context/set_decode_mode.c \
						encode/context/set_encode_mode.c \
						encode/context/set_input_file.c \
						encode/context/set_output_file.c \
						\
						cipher/context/cphr_argv_state_a.c \
						cipher/context/cphr_argv_state_d.c \
						cipher/context/cphr_argv_state_e.c \
						cipher/context/cphr_argv_state_i.c \
						cipher/context/cphr_argv_state_k.c \
						cipher/context/cphr_argv_state_o.c \
						cipher/context/cphr_argv_state_p.c \
						cipher/context/cphr_argv_state_s.c \
						cipher/context/cphr_argv_state_v.c \
						cipher/context/cphr_is_a_flag.c \
						cipher/context/cphr_is_decrypt_mode.c \
						cipher/context/cphr_is_encrypt_mode.c \
						cipher/context/cphr_is_iv_set.c \
						cipher/context/cphr_is_key_set.c \
						cipher/context/cphr_is_pass_set.c \
						cipher/context/cphr_is_salt_set.c \
						cipher/context/des_argv_states.c \
						cipher/context/destruct_cipher_context.c \
						cipher/context/init_cipher_context.c \
						cipher/context/set_cipher_bufsize.c \
						cipher/context/set_cipher_init_vector.c \
						cipher/context/set_cipher_input_file.c \
						cipher/context/set_cipher_key.c \
						cipher/context/set_cipher_output_file.c \
						cipher/context/set_cipher_pass_salt.c \
						cipher/context/set_cipher_password_from_stdin.c \
						cipher/context/set_cipher_random_pass_salt.c \
						\
						cipher/des/des.c \
						cipher/des/des_cbc.c \
						cipher/des/des_cbc_decrypt.c \
						cipher/des/des_cbc_encrypt.c \
						cipher/des/des_cut_padding.c \
						cipher/des/des_ecb.c \
						cipher/des/des_ecb_decrypt.c \
						cipher/des/des_ecb_encrypt.c \
						cipher/des/des_encode_block.c \
						cipher/des/des_get_block.c \
						cipher/des/des_key_gen.c \
						cipher/des/des_permutation.c \
						cipher/des/des_swap_block_halves.c \
						cipher/des/s_permutation.c \
						cipher/des/try_get_des_salt_from_fd.c \
						\
						cipher/pbkdf/pbkdf_md5.c

OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(PROJECT)


$(PROJECT): $(OBJECTS)
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	@echo "Compiled!"

.c.o:
	@$(CC) $(CFLAGS) $< -o $@

allcl: all clean

clean:
	@rm -rf $(OBJECTS)
	@echo "Object files removed"

fclean: clean
	@rm  -f ${PROJECT}
	@echo ${PROJECT} removed

re: fclean all
