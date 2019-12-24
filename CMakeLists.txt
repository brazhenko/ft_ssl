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

set(MD5_SRC md5/calculate_md5_block.c
			md5/calculate_md5_buf_padding.c
			md5/calculate_md5_from_fd.c
			md5/calculate_md5_from_string.c
			md5/md5.c
			md5/print_md5.c)

set(SHA256_SRC	sha256/calc_sha256_buf_padding.c
				sha256/calc_sha256_from_fd.c
				sha256/calc_sha256_from_string.c
				sha256/print_sha256.c
				sha256/sha256.c)

set(SHA384_SRC)
set(SHA512_SRC)
set(BASE64_SRC		base64/base64.c
		base64/context/init_base64_context.c
		base64/context/set_decode_mode.c
		base64/context/set_encode_mode.c
		base64/context/set_input_file.c
		base64/context/set_output_file.c
		base64/context/parse_base64_argv.c
		base64/context/base64_states.c
		base64/base64_decode.c base64/base64_encode.c base64/encode_usage.c base64/context/argv_errors.c)

set(DES_SRC des/context/des_argv_states.c des/context/init_des_context.c)

SET(UTILITIES_SRC	utilities/is_flag.c
					utilities/nstrjoin.c
					utilities/xmalloc.c
					utilities/print_uint32_bits.c
		)


add_executable(
				${PROJECT_NAME}
				${FT_SSL_SRC}
				${MD5_SRC}
				${SHA256_SRC}
				${BASE64_SRC}
				${DES_SRC}
				${UTILITIES_SRC}
)

