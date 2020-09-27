//
// Created by 17641238 on 27.09.2020.
//

#include <utilities.h>
#include <printf.h>
#include "rsautl_context.h"


void	rsautl(int ac, char **av)
{
	t_rsautl_context		*ctx;

	ctx = init_rsautl_ctx();
	ctx = parse_rsautl_argv(ac, av, ctx);


	uint64_t crypto = fast_mod_pow(123, 65537, 15702980669118530159U);
	uint64_t plain = fast_mod_pow(crypto, 11744469537637774145U, 15702980669118530159U);
	printf("crypto: %llu, plain: %llu\n", crypto, plain);

}