cmake_minimum_required(VERSION 3.8)
project(ft_ssl C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")
set(GCC_COVERAGE_LINK_FLAGS    "-Wall -Wextra -Werror")

include_directories("include")

set(FT_SSL_SRC	ssl/command_executor.c
				ssl/hash_executor.c
				ssl/help.c
				ssl/main.c
				ssl/parse_hash_flags.c
				ssl/encode_executor.c)

set(MD5_SRC hash/md5/calculate_md5_block.c
		hash/md5/calculate_md5_buf_padding.c
		hash/md5/calculate_md5_from_fd.c
		hash/md5/calculate_md5_from_string.c
		hash/md5/md5.c
		hash/md5/print_md5.c)

set(SHA256_SRC hash/sha256/calc_sha256_buf_padding.c
		hash/sha256/calc_sha256_from_fd.c
		hash/sha256/calc_sha256_from_string.c
		hash/sha256/print_sha256.c
		hash/sha256/sha256.c)

set(SHA384_SRC)
set(SHA512_SRC)
set(BASE64_SRC encode/base64/base64.c
		encode/context/init_encode_context.c
		encode/context/set_decode_mode.c
		encode/context/set_encode_mode.c
		encode/context/set_input_file.c
		encode/context/set_output_file.c
		encode/context/parse_encode_argv.c
		encode/context/encode_argv_states.c
		encode/base64/base64_decode.c
		encode/base64/base64_encode.c
		encode/encode_usage.c encode/context/argv_errors.c
		encode/context/destruct_encode_context.c
		include/encode_context.h)

set(DES_SRC
		include/cipher_context.h
		cipher/context/des_argv_states.c
		cipher/context/init_cipher_context.c
		cipher/context/set_cipher_input_file.c
		cipher/context/set_cipher_output_file.c
		cipher/des/des_ecb.c
		cipher/des/des_cbc.c
		cipher/des/des_cfb.c
		cipher/des/des_ofb.c
		cipher/des/des_ctr.c
		cipher/des/des_3des.c
		cipher/des/des_3des_encode.c
		cipher/des/des_3des_decode.c
		cipher/des/des_cbc_encode.c
		cipher/des/des_cbc_decode.c
		cipher/des/des_cfb_encode.c
		cipher/des/des_cfb_decode.c
		cipher/des/des_ctr_encode.c
		cipher/des/des_ctr_decode.c
		cipher/des/des_ecb_encode.c
		cipher/des/des_ecb_decode.c
		cipher/des/des_ofb_encode.c
		cipher/des/des_ofb_decode.c cipher/context/set_cipher_bufsize.c cipher/des/des_get_block.c cipher/des/des_ip.c cipher/des/des_key_gen.c cipher/des/des_block_debug.c cipher/des/des_encode_block.c cipher/context/set_cipher_key.c ssl/cipher_executor.c cipher/context/set_cipher_pass_salt.c cipher/context/destruct_cipher_context.c cipher/des/des_permutation.c cipher/des/des_swap_block_halves.c)

SET(UTILITIES_SRC ssl/utilities/is_flag.c
		ssl/utilities/nstrjoin.c
		ssl/utilities/xmalloc.c
		ssl/utilities/print_uint32_bits.c
		ssl/utilities/print_uint64_bits.c ssl/utilities/mem_xor.c)
add_executable(
				${PROJECT_NAME}
				${FT_SSL_SRC}
				${MD5_SRC}
				${SHA256_SRC}
				${BASE64_SRC}
				${DES_SRC}
				${UTILITIES_SRC}
)

