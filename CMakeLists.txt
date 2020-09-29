cmake_minimum_required(VERSION 3.8)
project(ft_ssl C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")
set(GCC_COVERAGE_LINK_FLAGS    "-Wall -Wextra -Werror")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

include_directories("include")

set(FT_SSL_SRC
		ssl/command_executor.c
		ssl/hash_executor.c
		ssl/help.c
		ssl/main.c
		ssl/parse_hash_flags.c
		ssl/encode_executor.c
		ssl/wrong_command_exit.c)

set(MD5_SRC
		hash/md5/calculate_md5_block.c
		hash/md5/calculate_md5_buf_padding.c
		hash/md5/calculate_md5_from_fd.c
		hash/md5/calculate_md5_from_string.c
		hash/md5/md5.c
		hash/md5/print_md5.c
		hash/md5/calculate_md5_from_mem.c)

set(SHA256_SRC
		hash/sha256/calc_sha256_buf_padding.c
		hash/sha256/calc_sha256_from_fd.c
		hash/sha256/calc_sha256_from_string.c
		hash/sha256/print_sha256.c
		hash/sha256/sha256.c)

set(SHA384_SRC)
set(SHA512_SRC)

set(BASE64_SRC
		encode/base64/base64.c
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
		cipher/des/des_cbc_encrypt.c
		cipher/des/des_cbc_decrypt.c
		cipher/des/des_ecb_encrypt.c
		cipher/des/des_ecb_decrypt.c
		cipher/context/set_cipher_bufsize.c
		cipher/des/des_get_block.c
		cipher/des/des_key_gen.c
		cipher/des/des_encode_block.c
		cipher/context/set_cipher_key.c
		ssl/cipher_executor.c
		cipher/context/set_cipher_pass_salt.c
		cipher/context/destruct_cipher_context.c
		cipher/des/des_permutation.c
		cipher/des/des_swap_block_halves.c
		cipher/context/set_cipher_init_vector.c
		cipher/context/set_cipher_password_from_stdin.c
		cipher/context/set_cipher_random_pass_salt.c
		cipher/des/try_get_des_salt_from_fd.c
		cipher/des/s_permutation.c
		cipher/pbkdf/pbkdf_md5.c
		include/pbkdf.h
		cipher/des/des.c
		cipher/des/des_cut_padding.c
		cipher/context/cphr_is_a_flag.c
		cipher/context/cphr_is_decrypt_mode.c
		cipher/context/cphr_is_encrypt_mode.c
		cipher/context/cphr_is_iv_set.c
		cipher/context/cphr_is_key_set.c
		cipher/context/cphr_is_pass_set.c
		cipher/context/cphr_is_salt_set.c
		cipher/context/cphr_argv_state_a.c
		cipher/context/cphr_argv_state_d.c
		cipher/context/cphr_argv_state_e.c
		cipher/context/cphr_argv_state_i.c
		cipher/context/cphr_argv_state_k.c
		cipher/context/cphr_argv_state_o.c
		cipher/context/cphr_argv_state_p.c
		cipher/context/cphr_argv_state_s.c
		cipher/context/cphr_argv_state_v.c)

SET(UTILITIES_SRC
		ssl/utilities/is_flag.c
		ssl/utilities/nstrjoin.c
		ssl/utilities/xmalloc.c
		ssl/utilities/print_uint32_bits.c
		ssl/utilities/print_uint64_bits.c
		ssl/utilities/mem_xor.c
		ssl/utilities/print_hex_memory.c
		ssl/utilities/solovay_strassen_test.c
		ssl/utilities/smax.c ssl/utilities/fatal.c ssl/utilities/int128convs.c)

SET(BIGINT_SRC
		multiprecision_lib/multiprecision.h
		multiprecision_lib/multiprecision1.c)

SET(RSA_SRC
		include/rsa.h
		rsa/genrsa/genrsa.c
		rsa/genrsa_ctx/parse_gen_rsa_args.c
		include/genrsa_context.h
		rsa/rsa_ctx/parse_rsa_args.c
		include/rsa_context.h
		rsa/rsa/rsa.c
		include/key_io.h
		rsa/key_io/output_routines.c
		rsa/key_io/input_routines.c rsa/key_io/routines1.c rsa/key_io/routines2.c rsa/key_io/internal_key_io.h rsa/rsautl/rsautl.c include/rsautl_context.h "rsa/rsautl_ctx/parse_rsautl_args.c" rsa/rsa/rsa2.c rsa/rsa_breaker/rsa_breaker.c rsa/rsautl_ctx/parse_rsautl2.c rsa/rsautl_ctx/parse_rsautl_internal.h rsa/rsautl/rsa_utl_routines.c rsa/rsautl/internal_rsautl.h rsa/rsa_ctx/internal_rsa_ctx.h rsa/rsa/internal_rsa.h)

SET(TEST
		include/.tests.h
		tests/.tests.c ssl/utilities/mod_inverse.c rsa/genrsa_ctx/genrsa_ctx2.c rsa/rsa_ctx/rsa_ctx2.c rsa/genrsa_ctx/internal_genrsa_ctx.h)

add_executable(
		${PROJECT_NAME}
		${FT_SSL_SRC}
		${MD5_SRC}
		${SHA256_SRC}
		${BASE64_SRC}
		${DES_SRC}
		${UTILITIES_SRC}
		${BIGINT_SRC}
		${RSA_SRC}
		${TEST})

