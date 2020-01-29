#include <cipher_context.h>
#include <des.h>
#include <string.h>

/*
** TODO think of another way to cut padding....
*/

void		des_cut_padding(t_cipher_context *ctx, t_lpdesblock block)
{
	if (memcmp(((unsigned char *)block) + 7, "\1", 1) == 0)
		(*block)[7] = 0;
	else if (memcmp(((unsigned char *)block) + 6, "\2\2", 2) == 0)
		(*block)[6] = 0;
	else if (memcmp(((unsigned char *)block) + 5, "\3\3\3", 3) == 0)
		(*block)[5] = 0;
	else if (memcmp(((unsigned char *)block) + 4, "\4\4\4\4", 4) == 0)
		(*block)[4] = 0;
	else if (memcmp(((unsigned char *)block) + 3, "\5\5\5\5\5", 5) == 0)
		(*block)[3] = 0;
	else if (memcmp(((unsigned char *)block) + 2, "\6\6\6\6\6\6", 6) == 0)
		(*block)[2] = 0;
	else if (memcmp(((unsigned char *)block) + 1, "\7\7\7\7\7\7\7", 7) == 0)
		(*block)[1] = 0;
	else if (memcmp(((unsigned char *)block) + 0,
			"\10\10\10\10\10\10\10\10", 8) == 0)
		(*block)[0] = 0;
}
