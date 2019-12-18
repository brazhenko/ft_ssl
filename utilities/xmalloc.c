#include <stdlib.h>
#include <unistd.h>

void	*xmalloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret)
	{
		return (ret);
	}
	write(2, "malloc() error\nexit\n", 20);
	exit(1);
	return (NULL);
}