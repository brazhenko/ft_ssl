cmake_minimum_required(VERSION 3.8)
project(ft_ssl C)

set(CMAKE_C_STANDARD 99)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")
set(GCC_COVERAGE_LINK_FLAGS    "-Wall -Wextra -Werror")

include_directories("include")

set(FT_SSL_SRC	ssl/command_executor.c
				ssl/hash_executor.c
				ssl/help.c
				ssl/main.c
				ssl/parse_hash_flags.c ssl/encode_executor.c)

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
set(BASE64_SRC		base64/base64.c)

SET(UTILITIES_SRC	utilities/is_flag.c
					utilities/nstrjoin.c)


add_executable(
				${PROJECT_NAME}
				${FT_SSL_SRC}
				${MD5_SRC}
				${SHA256_SRC}
				${BASE64_SRC}
				${UTILITIES_SRC}
)

